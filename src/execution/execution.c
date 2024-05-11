/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:00:39 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/11 08:26:00 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_envp(t_expand *lst_envp)
{
	t_expand	*head;
	size_t		size;
	char		**envp;
	int			i;

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
		envp[i] = ft_strjoin_env(head->key, "=");
		envp[i] = ft_strjoin_env(envp[i], head->value);
		i++;
		head = head->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	ft_execution(t_cmd *cmd, t_expand **envp, int *exit_status)
{
	char	**env;

	env = NULL;
	if (!envp)
	{
		perror("no env");
		exit(1);
	}
	env = get_envp(*envp);
	set_cmd_false_true(&cmd);
	pipe_line(cmd, envp, env, exit_status);
}

void	ft_execute_bultin_part2(char *cmd[], t_expand **envp, int *exit_status)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
	{
		exit(ft_cd(cmd[1], *envp));
	}
	if (ft_strcmp(cmd[0], "pwd") == 0)
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

void	ft_execute_bultin(char *cmd[], t_expand **envp, int *exit_status)
{
	if (!cmd || !*cmd)
		return ;
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		ft_echo(cmd);
		exit(0);
	}
	if (ft_strcmp(cmd[0], "export") == 0)
	{
		exit(ft_export(cmd, envp));
	}
	if (ft_strcmp(cmd[0], "env") == 0)
	{
		ft_env(cmd, *envp);
		exit(0);
	}
	ft_execute_bultin_part2(cmd, envp, exit_status);
}

void	ft_execute_node(char *cmd[], t_expand *envp,
		char **str_envp, int *exit_status)
{
	char	**paths;
	char	*new_cmd;

	paths = NULL;
	if (!cmd || !*cmd)
		exit(0);
	ft_execute_bultin(cmd, &envp, exit_status);
	while (envp)
	{
		if (ft_strcmp(envp->key, "PATH") == 0)
			break ;
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
