/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 02:14:56 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/30 12:43:53 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand *get_oldpwd(t_expand *env)
{
	t_expand *oldpwd;

	oldpwd = env;
	while (oldpwd)
	{
		if ((ft_strcmp(oldpwd->key, "OLDPWD") == 0))
			return (oldpwd);
		oldpwd = oldpwd->next;
	}
	return (NULL);
}

t_expand *get_pwd(t_expand *env)
{
	t_expand *pwd;

	pwd = env;
	while (pwd)
	{
		if ((ft_strcmp(pwd->key, "PWD") == 0))
			return (pwd);
		pwd = pwd->next;
	}
	return (NULL);
}

char *get_home(t_expand *env)
{
	t_expand *pwd;

	pwd = env;
	while (pwd)
	{
		if ((ft_strcmp(pwd->key, "HOME") == 0))
			return (pwd->value);
		pwd = pwd->next;
	}
	return (NULL);
}

int ft_cd(char *path, t_expand *env)
{
	t_expand *oldpwd;
	t_expand *new_pwd;
	char op[PATH_MAX];
	char np[PATH_MAX];
	char *home;

	getcwd(op, PATH_MAX);
	if (!path || ft_strcmp(path, "~") == 0)
	{
		home = get_home(env);
		if (home)
			path = ft_strdup_env(home);
		else
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	if (ft_strcmp(path, "-") == 0)
	{
		oldpwd = get_oldpwd(env);
		if (!oldpwd || !*oldpwd->value)
		{
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
			return (1);
		}
		else
		{
			path = oldpwd->value;
			printf("%s\n", path);
		}
	}
	if (chdir(path) < 0)
	{
		perror("cd");
		return (1);
	}
	if (!getcwd(np, PATH_MAX))
	{
		ft_putendl_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory", 2);
		return (0);
	}
	oldpwd = get_oldpwd(env);
	if (oldpwd)
	{
		if (oldpwd->value)
		{

			free(oldpwd->value);
			oldpwd->value = NULL;
		}
		oldpwd->value = ft_strdup_env(op);
		oldpwd->isnull = false;
	}
	new_pwd = get_pwd(env);
	if (new_pwd)
	{
		if (new_pwd->value)
		{
			free(new_pwd->value);
			new_pwd->value = NULL;
		}
		new_pwd->value = ft_strdup_env(np);
	}
	return (0);
}
