/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 02:14:56 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/06 05:53:42 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand *get_oldpwd(t_expand *env)
{
	t_expand *oldpwd;

	oldpwd = env;
	while(oldpwd)
	{
		if((ft_strcmp(oldpwd->key, "OLDPWD") == 0))
			return (oldpwd);
		oldpwd = oldpwd->next;
	}
	return (NULL);
}

t_expand *get_pwd(t_expand *env)
{
	t_expand *pwd;

	pwd = env;
	while(pwd)
	{
		if((ft_strcmp(pwd->key, "PWD") == 0))
			return (pwd);
		pwd = pwd->next;
	}
	return (NULL);
}

char *get_home(t_expand *env)
{
	t_expand *pwd;

	pwd = env;
	while(pwd)
	{
		if((ft_strcmp(pwd->key, "HOME") == 0))
			return (pwd->value);
		pwd = pwd->next;
	}
	return (NULL);
}

void	ft_cd(char *path, t_expand *env)
{
	t_expand 	*oldpwd;
	t_expand 	*new_pwd;
	char	op[PATH_MAX];
	char	np[PATH_MAX];

	getcwd(op, PATH_MAX);
	if(!path || ft_strcmp(path, "~") == 0)
		path = ft_strdup(get_home(env));
	if (chdir(path) < 0)
		return (perror("cd "));
	getcwd(np, PATH_MAX);
	oldpwd = get_oldpwd(env);
	if(oldpwd)
	{
		if(oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = ft_strdup(op);
	}
	new_pwd = get_pwd(env);
	if(new_pwd)
	{
		if(new_pwd->value)
			free(new_pwd->value);
		new_pwd->value = ft_strdup(np);
	}
}
