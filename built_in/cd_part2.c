/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_part2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 03:27:41 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/07 04:25:02 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(t_expand **env)
{
	char *cmd[] = {"export", "PWD", NULL};
    
	ft_export(cmd, env);
}

void	change_oldpwd(t_expand **env)
{
	char *cmd[] = {"export", "OLDPWD", NULL};
    
	ft_export(cmd, env);
}

t_expand	*get_oldpwd(t_expand *env)
{
	t_expand	*oldpwd;

	oldpwd = env;
	while (oldpwd)
	{
		if ((ft_strcmp(oldpwd->key, "OLDPWD") == 0))
			return (oldpwd);
		oldpwd = oldpwd->next;
	}
	return (NULL);
}

t_expand	*get_pwd(t_expand *env)
{
	t_expand	*pwd;

	pwd = env;
	while (pwd)
	{
		if ((ft_strcmp(pwd->key, "PWD") == 0))
			return (pwd);
		pwd = pwd->next;
	}
	return (NULL);
}

char	*get_home(t_expand *env)
{
	t_expand	*pwd;

	pwd = env;
	while (pwd)
	{
		if ((ft_strcmp(pwd->key, "HOME") == 0))
			return (pwd->value);
		pwd = pwd->next;
	}
	return (NULL);
}
