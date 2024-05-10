/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:00:39 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/09 20:20:57 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **get_envp(t_expand *lst_envp)
{
	t_expand *head;
	size_t size;
	char **envp;
	int i;

	i = 0;
	head = lst_envp;
	if (lst_envp == NULL)
		return (NULL);
	size = ft_lst_size(lst_envp);
	if (size == 0)
		return (NULL);
	envp = (char **)ft_malloc_env((size + 1) * sizeof(char *), ALLOC);
	if (!envp)
		return (perror("malloc"), NULL);
	while (head)
	{
		// TO_DO:ft_strjoin fail case
		envp[i] = ft_strjoin_env(head->key, "=");
		envp[i] = ft_strjoin_env(envp[i], head->value);
		i++;
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}

void ft_execution(t_cmd *cmd, t_expand **envp, int *exit_status)
{
	char **env = NULL;

	if (!envp)
	{
		perror("no env");
		exit(1);
	}
	env = get_envp(*envp);
	// if (!env)
	// 	return ;
	set_cmd_false_true(&cmd);
	pipe_line(cmd, envp, env, exit_status);
}
void ft_execute_bultin(char *cmd[], t_expand **envp, int *exit_status)
{
	(void)exit_status;
	if (!cmd || !*cmd)
		return;
	if (ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "/bin/echo") == 0)
	{
		ft_echo(cmd);
		exit(0);
	}
	if (ft_strcmp(cmd[0], "export") == 0)
	{
		exit(ft_export(cmd, envp));
	}
	if (ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "/usr/bin/env") == 0)
	{
		ft_env(cmd, *envp);
		exit(0);
	}
	if (ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "/usr/bin/cd") == 0)
	{
		exit(ft_cd(cmd[1], *envp));
	}
	if (ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "/bin/pwd") == 0)
	{
		ft_pwd(*envp);
		exit(0);
	}
	if (ft_strcmp(cmd[0], "unset") == 0)
	{
		exit(ft_unset(cmd, envp));
	}
	if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd, *exit_status);
}

void no_path_error(char *cmd)
{
	DIR *mydir;

	mydir = NULL;
	if ((mydir = opendir(cmd)) && mydir)
	{
		closedir(mydir);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		exit(126);
	}
	if (access(cmd, X_OK) && access(cmd, F_OK))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
}

void direct_cmd_error(char *cmd)
{
	DIR *mydir;

	mydir = NULL;
	if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	if ((mydir = opendir(cmd)) && mydir && ft_strcmp(cmd, "..") && ft_strcmp(cmd, "."))
	{
		closedir(mydir);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		exit(126);
	}
}

void exit_127(char *cmd, char *error)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(error, 2);
	exit(127);
}
char	*check_path(char **path, char *cmd)
{
	char *cmd_path;
	int i;

	i = 0;
	if ((!path || !*path))
		no_path_error(cmd);
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (access(cmd, X_OK) == 0 || access(cmd, F_OK) == 0)
		{
			direct_cmd_error(cmd);
			return (cmd);
		}
		exit_127(cmd, ": No such file or directory");
	}
	while (path[i])
	{
		cmd_path = ft_strjoin_env("/", cmd);
		cmd_path = ft_strjoin_env(path[i], cmd_path);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
		cmd_path = NULL;
	}
	return (exit_127(cmd, ": command not found"), NULL);
}

int ft_count_word(char **output)
{
	int i = 0;
	if (!output)
		return (0);
	while (output[i])
		i++;
	return (i);
}

void ft_execute_node(char *cmd[], t_expand *envp, char **str_envp, int *exit_status)
{
	char **paths;
	char *new_cmd;

	paths = NULL;
	if (!cmd || !*cmd)
		exit(0);
	ft_execute_bultin(cmd, &envp, exit_status);
	while (envp)
	{
		if (ft_strcmp(envp->key, "PATH") == 0)
			break;
		envp = envp->next;
	}
	if (envp)
		paths = ft_split(envp->value, ':');
	new_cmd = check_path(paths, cmd[0]);
	execve(new_cmd, cmd, str_envp);
	if ((access(new_cmd, X_OK) == 0))
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
	}
	else
		perror(cmd[0]);
	exit(127);
}
