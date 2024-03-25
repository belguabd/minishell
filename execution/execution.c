/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:00:39 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/25 02:29:56 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_expand *cmd, t_expand *envp)
{
	
	
}
char	**get_envp(t_expand *lst_envp)
{
	size_t	size;
	char	**envp;
	int		i;

	i = 0;
	size = ft_lst_size(envp);
	if (size == 0)
		return (NULL);
	envp = (char **)malloc((size + 1) * sizeof(char *));
	if (!envp)
		perror("malloc");
	while (lst_envp)
	{
		//TO_DO:ft_strjoin fail case
		envp[i] = ft_strjoin(lst_envp->key, "=");
		envp[i] = ft_strjoin(envp[i], lst_envp->value);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

void	ft_execute_node(char *cmd[], t_expand *envp, char **str_envp)
{
	char	**paths;

	while (envp)
	{
		if (ft_strcmp(envp->key, "PATH") == 0)
			break ;
		envp = envp->next;
	}
	if (envp)
		paths = ft_split(envp->value, ":");
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
	execve(cmd[0], cmd, str_envp);
	perror(cmd[0]);
}
