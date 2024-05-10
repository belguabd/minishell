/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 04:58:53 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 08:42:33 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	no_path_error(char *cmd)
{
	DIR	*mydir;

	mydir = NULL;
	mydir = opendir(cmd);
	if (mydir)
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

void	direct_cmd_error(char *cmd)
{
	DIR	*mydir;

	mydir = NULL;
	if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	mydir = opendir(cmd);
	if (mydir && ft_strcmp(cmd, "..") && ft_strcmp(cmd, "."))
	{
		closedir(mydir);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": is a directory", 2);
		exit(126);
	}
}

void	exit_127(char *cmd, char *error)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(error, 2);
	exit(127);
}

char	*check_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

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
