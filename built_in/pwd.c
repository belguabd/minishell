/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:39:25 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/26 23:14:04 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

t_expand *get_pwd_cd(t_expand *env)
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

void	ft_pwd(t_expand *env)
{
	char	path[PATH_MAX];
	static char	static_path[PATH_MAX];
	t_expand *pwd_path = NULL;

	if (getcwd(path, PATH_MAX) != NULL)
	{
		printf("%s\n", path);
		memcpy(static_path, path, ft_strlen(path));
	}
	else if(!*static_path)
	{
		pwd_path = get_pwd_cd(env);
		if(pwd_path)
			printf("%s\n", pwd_path->value);
	}
	else
		printf("%s\n", static_path);
}

