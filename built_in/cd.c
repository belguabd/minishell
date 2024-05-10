/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 02:14:56 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/09 02:40:10 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	go_to_home(t_expand *env, char **path)
{
	char	*home;

	home = get_home(env);
	if (home)
		*path = ft_strdup_env(home);
	else
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	return (0);
}

int	go_to_oldpwd(t_expand *env, t_expand *oldpwd, char **path)
{
	oldpwd = get_oldpwd(env);
	if (!oldpwd || !*oldpwd->value)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	else
	{
		*path = oldpwd->value;
		printf("%s\n", *path);
	}
	return (0);
}

void	ft_change_oldpwd(t_expand *oldpwd, t_expand *env, char *op)
{
	oldpwd = get_oldpwd(env);
	if (oldpwd)
	{
		if (oldpwd->value)
		{
			//free(oldpwd->value);
			oldpwd->value = NULL;
		}
		oldpwd->value = ft_strdup_env(op);
		oldpwd->isnull = false;
	}
}
void	ft_change_pwd(t_expand *new_pwd, t_expand *env, char *np)
{
	new_pwd = get_pwd(env);
	if (new_pwd)
	{
		if (new_pwd->value)
		{
			//free(new_pwd->value);
			new_pwd->value = NULL;
		}
		new_pwd->value = ft_strdup_env(np);
		new_pwd->isnull = false;
	}
}

int	ft_cd_home_and_oldpath(char **path, t_expand *env, t_expand *oldpwd)
{
	if (!*path || ft_strcmp(*path, "~") == 0)
	{
		if (go_to_home(env, path) == 1)
			return (1);
	}
	if (ft_strcmp(*path, "-") == 0)
	{
		if (go_to_oldpwd(env, oldpwd, path) == 1)
			return (1);
	}
	return (0);
}

int	ft_cd(char *path, t_expand *env)
{
	//TODO : CHANGE t_expand *env to **env in case of no nodes in the env
	t_expand	*oldpwd;
	t_expand	*new_pwd;
	char		op[PATH_MAX];
	char		np[PATH_MAX];

	oldpwd = NULL;
	new_pwd = NULL;
	change_oldpwd(&env);
	change_pwd(&env);
	strlcpy(op, ft_get_cwd(NULL, 0), PATH_MAX);
	if (ft_cd_home_and_oldpath(&path, env, oldpwd) == 1)
		return (1);
	if (chdir(path) < 0)
		return (perror("cd"), 1);
	strlcpy(np, ft_get_cwd(NULL, 0), PATH_MAX);
	if (!getcwd(np, PATH_MAX))
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		ft_get_cwd(path, 1);
		strlcpy(np, ft_get_cwd(NULL, 0), PATH_MAX);
	}
	ft_change_oldpwd(oldpwd, env, op);
	ft_change_pwd(new_pwd, env, np);
	return (0);
}
