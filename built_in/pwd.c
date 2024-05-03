/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:39:25 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/02 15:14:37 by soel-bou         ###   ########.fr       */
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

char *ft_get_cwd(char *new_path, int mode)
{
	char		path[PATH_MAX];
	static char	static_path[PATH_MAX];
	
	if (getcwd(path, PATH_MAX) != NULL)
	{
		strlcpy(static_path, path, PATH_MAX);
		return (static_path);
	}
	if (mode == 1)
	{
		strlcat(static_path, "/", PATH_MAX);
		strlcat(static_path, new_path, PATH_MAX);
	}
	return (static_path);
}

void	ft_pwd(t_expand *env)
{
	char *path;
	
	(void)env;
	path = ft_get_cwd(NULL, 0);
	printf("%s\n", path);
}

