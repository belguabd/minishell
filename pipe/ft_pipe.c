/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:20:36 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/22 15:18:38 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int *allocat_pids(t_cmd *cmd)
{
	t_cmd *tmp;
	int i;
	int *pids;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	pids = (int *)ft_malloc(i * sizeof(int),ALLOC);
	if (!pids)
	{
		perror("faild to allocat memory for pids");
		exit(1);
	}
	return (pids);
}

void init_fds(t_cmd **cmds)
{
	t_cmd *head;
	token_node *tmp;
	int old_fd_in;
	int old_fd_out;

	head = *cmds;
	tmp = head->redir;
	old_fd_in = -2;
	old_fd_out = -2;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->type == REDIRECT_OUT)
			{
				head->outfile = open(tmp->value, O_RDWR | O_CREAT | O_TRUNC, 0777);
				if (head->outfile < 0)
					perror("fd_out");
			}
			else if (tmp->type == REDIRECT_APPEND)
			{
				head->outfile = open(tmp->value, O_RDWR | O_CREAT | O_APPEND, 0777);
				if (head->outfile < 0)
					perror("fd_app");
			}
			else if (tmp->type == REDIRECT_IN)
			{
				head->infile = open(tmp->value, O_RDWR, 0777);
				if (head->infile < 0)
				{
					perror(tmp->value);
					return;
				}
			}
			else if (tmp->type == HEREDOC)
			{
				head->infile = open(tmp->value, O_RDWR | O_CREAT, 0777);
				if (head->infile < 0)
				{
					perror(tmp->value);
					return;
				}
			}
			tmp = tmp->next;
		}
	}
	else
	{
		head->infile = 0;
		head->outfile = 1;
	}
}

void pipe_line(t_cmd *cmd, t_expand *env_lst, char *env[])
{
	if (!cmd)
		return;
	int fd[2];
	int *pid;
	int tmp_fd_in;
	int i = 0;

	tmp_fd_in = -1;
	pid = allocat_pids(cmd);
	init_fds(&cmd);
	if (exe_one_cmd_only(cmd, env_lst))
		return;
	while (cmd)
	{
		init_fds(&cmd);
		if (!cmd->islast)
			pipe(fd);
		pid[i] = fork();
		if (pid[i] < 0)
			perror("fork");
		if (pid[i] == 0)
		{
			if (cmd->infile != 0)
			{
				if (cmd->infile == -1)
					exit(0);
				if ((dup2(cmd->infile, 0) < 0))
					exit(0);
				close(cmd->infile);
			}
			if (cmd->outfile != 1)
			{
				if (cmd->outfile == -1)
					exit(0);
				if ((dup2(cmd->outfile, 1) < 0))
					close(1);
				close(cmd->outfile);
			}
			if (!cmd->isfirst)
			{
				dup2(tmp_fd_in, cmd->infile);
				close(tmp_fd_in);
			}
			if (!cmd->islast)
			{
				if (dup2(fd[1], cmd->outfile) < 0)
					close(cmd->outfile);
				close(fd[1]);
				close(fd[0]);
			}
			ft_execute_node(cmd->args, env_lst, env);
			exit(EXIT_SUCCESS);
		}
		if (!cmd->isfirst)
			close(tmp_fd_in);
		if (!cmd->islast)
		{
			close(fd[1]);
			tmp_fd_in = fd[0];
			if (tmp_fd_in < 0)
				perror("tmp_fd_in");
		}
		cmd = cmd->next;
		i++;
	}
	while (i--)
		waitpid(pid[i], NULL, 0);
	free(pid);
	close(fd[0]);
	close(fd[1]);
}

int exe_one_cmd_only(t_cmd *cmd, t_expand *env)
{
	int save_in;
	int save_out;

	if (cmd->isfirst && cmd->islast && is_builtin(cmd))
	{
		save_in = dup(0);
		save_out = dup(1);
		if (cmd->infile != 0)
		{
			if ((dup2(cmd->infile, 0) < 0))
				return (1);
			close(cmd->infile);
		}
		if (cmd->outfile != 1)
		{
			if ((dup2(cmd->outfile, 1) < 0))
				return (1);
			close(cmd->outfile);
		}
		if (!exe_bultin_in_parent(cmd->args, env))
			return (0);
		if ((dup2(save_in, 0) < 0))
			close(0);
		close(save_in);
		if ((dup2(save_out, 1) < 0))
			close(1);
		close(save_out);
		return (1);
	}
	return (0);
}

int is_builtin(t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (0);
	if ((ft_strcmp(cmd->args[0], "echo") == 0) || (ft_strcmp(cmd->args[0], "export") == 0) || (ft_strcmp(cmd->args[0], "env") == 0) || (ft_strcmp(cmd->args[0], "cd") == 0) || (ft_strcmp(cmd->args[0], "pwd") == 0) || (ft_strcmp(cmd->args[0], "unset") == 0) || (ft_strcmp(cmd->args[0], "/bin/echo") == 0) || (ft_strcmp(cmd->args[0], "/usr/bin/cd") == 0) || (ft_strcmp(cmd->args[0], "/usr/bin/env") == 0) || (ft_strcmp(cmd->args[0], "/bin/pwd") == 0) || (ft_strcmp(cmd->args[0], "exit") == 0))
		return (1);
	return (0);
}

int exe_bultin_in_parent(char *cmd[], t_expand *env)
{
	if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "/bin/echo") == 0)
		return (ft_echo(cmd), 1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd), 1);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(cmd, &env), 1);
	else if (ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "/usr/bin/env") == 0)
		return (ft_env(cmd, env), 1);
	else if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "/usr/bin/cd") == 0)
		return (ft_cd(cmd[1], env), 1);
	else if (ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "/bin/pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (ft_unset(cmd, &env), 1);
	return (0);
}