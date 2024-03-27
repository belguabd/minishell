/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:00:39 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/27 22:30:42 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **get_envp(t_expand *lst_envp)
{
	size_t size;
	char **envp;
	int i;

	i = 0;
	size = ft_lst_size(lst_envp);
	if (size == 0)
		return (NULL);
	envp = (char **)malloc((size + 1) * sizeof(char *));
	if (!envp)
		perror("malloc");
	while (lst_envp)
	{
		// TO_DO:ft_strjoin fail case
		envp[i] = ft_strjoin(lst_envp->key, "=");
		envp[i] = ft_strjoin(envp[i], lst_envp->value);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	ft_execution(t_cmd *cmd, t_expand **envp)
{
	char **env;

	env = get_envp(*envp);
	init_fds(&cmd);
	pipe_line(cmd, *envp, env);
}

// }

void ft_execute_bultin(char *cmd[], t_expand **envp)
{
	if(ft_strcmp(cmd[0], "echo") == 0 || ft_strcmp(cmd[0], "/bin/echo") == 0)
	{
		ft_echo(cmd);
		return;
	}
	if(ft_strcmp(cmd[0], "export") == 0 || ft_strcmp(cmd[0], "export"))
	{
		ft_export(cmd, envp);
		return;
	}
	if(ft_strcmp(cmd[0], "env") == 0 || ft_strcmp(cmd[0], "/usr/bin/env") == 0)
	{
		ft_env(cmd, *envp);
		return;
	}
	if(ft_strcmp(cmd[0], "cd") == 0 || ft_strcmp(cmd[0], "/usr/bin/cd") == 0)
	{
		ft_cd(cmd[0]);
		return;
	}
	if(ft_strcmp(cmd[0], "pwd") == 0 || ft_strcmp(cmd[0], "/bin/pwd") == 0)
	{
		ft_pwd();
		return;
	}
	if (ft_strcmp(cmd[0], "unset") == 0)
	{
		ft_unset(cmd, envp);
		return;
	}
}

void ft_execute_node(char *cmd[], t_expand *envp, char **str_envp)
{
	char **paths;
	(void)paths;

	ft_execute_bultin(cmd, &envp);
	while (envp)
	{
		if (ft_strcmp(envp->key, "PATH") == 0)
			break ;
		envp = envp->next;
	}
	if (envp)
		paths = ft_split(envp->value, ":");
	if(cmd[0][0] != '/')
	{
		cmd[0] = ft_strjoin("/", cmd[0]);
		if (!cmd[0])
			perror("malloc");
		while (*paths)
		{
			cmd[0] = ft_strjoin(*paths, cmd[0]);
			if (cmd[0])
				perror("malloc");
			if (!access(cmd[0], X_OK))
				break ;
		}
	}
	execve(cmd[0], cmd, str_envp);
	perror(cmd[0]);
}
