/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:20:36 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/26 22:58:50 by soel-bou         ###   ########.fr       */
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
	pids = (int *)ft_malloc_env(i * sizeof(int), ALLOC);
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

	// displayLinkedList(tmp);
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->type == REDIRECT_OUT)
			{
				if (tmp->flage)
				{
					perror("bash: ambiguous redirect");
					tmp->flage = false;
				}
				else
				{
					head->outfile = open(tmp->value, O_RDWR | O_CREAT | O_TRUNC, 0777);
					if (head->outfile > 2)
						ft_close_fds(head->outfile, OPEN);
					if (head->outfile < 0)
						perror("fd_out");
				}
			}
			else if (tmp->type == REDIRECT_APPEND)
			{
				if (tmp->flage)
				{
					perror("bash: ambiguous redirect");
					tmp->flage = false;
				}
				else
				{
					head->outfile = open(tmp->value, O_RDWR | O_CREAT | O_APPEND, 0777);
					if (head->outfile > 2)
						ft_close_fds(head->outfile, OPEN);
					if (head->outfile < 0)
						perror("fd_app");
				}
			}
			else if (tmp->type == REDIRECT_IN)
			{
				if (tmp->flage)
				{
					perror("bash: ambiguous redirect");
					tmp->flage = false;
				}
				else
				{

					head->infile = open(tmp->value, O_RDWR, 0777);
					if (head->infile > 2)
						ft_close_fds(head->infile, OPEN);
					if (head->infile < 0)
					{
						perror(tmp->value);
						return;
					}
				}
			}
			else if (tmp->type == HEREDOC)
			{
				head->infile = tmp->fd_hrd;
				if (head->infile > 2)
					ft_close_fds(head->infile, OPEN);
				if (head->infile < 0)
				{
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

void pipe_line(t_cmd *cmd, t_expand *env_lst, char *env[], int *exit_status)
{
	struct termios term;
	
	tcgetattr(STDIN_FILENO, &term);
	if (!cmd)
		return;
	int fd[2];
	int *pid;
	int tmp_fd_in;
	int i = 0;
	int j = 0;
	tmp_fd_in = -1;
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	pid = allocat_pids(cmd);
	init_fds(&cmd);
	if (exe_one_cmd_only(cmd, env_lst, exit_status))
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
					exit(1);
				if ((dup2(cmd->infile, 0) < 0))
					exit(1);
				close(cmd->infile);
			}
			if (cmd->outfile != 1)
			{
				if (cmd->outfile == -1)
					exit(1);
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
			ft_execute_node(cmd->args, env_lst, env, exit_status);
			exit(127);
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
	while (j < i)
		waitpid(pid[j++], exit_status, 0);
	if (WIFSIGNALED(*exit_status) && WTERMSIG(*exit_status) == SIGQUIT)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
		write(1, "\n", 1);
	}
	if (WIFEXITED(*exit_status))
		*exit_status = WEXITSTATUS(*exit_status);
	else if (WIFSIGNALED(*exit_status))
		*exit_status = WTERMSIG(*exit_status) + 128;
	// free(pid);
	close(fd[0]);
	close(fd[1]);
}

int exe_one_cmd_only(t_cmd *cmd, t_expand *env, int *exit_status)
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
		if (!exe_bultin_in_parent(cmd->args, env, exit_status))
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

int exe_bultin_in_parent(char *cmd[], t_expand *env, int *exit_status)
{
	*exit_status = 0;
	if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "/bin/echo") == 0)
		return (ft_echo(cmd), 1);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(cmd), 1);
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		*exit_status = ft_export(cmd, &env);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "/usr/bin/env") == 0)
		return (ft_env(cmd, env), 1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		*exit_status = ft_cd(cmd[1], env);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "/bin/pwd") == 0)
		return (ft_pwd(env), 1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		*exit_status = ft_unset(cmd, &env);
		return (1);
	}
	return (0);
}