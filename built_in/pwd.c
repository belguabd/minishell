/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:39:25 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/06 05:45:05 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

void	ft_pwd()
{
	char	path[PATH_MAX];
	static char	static_path[PATH_MAX];

	if (getcwd(path, PATH_MAX) != NULL)
	{
		printf("%s\n", path);
		memcpy(static_path, path, ft_strlen(path));
	}
	else
		printf("%s\n", static_path);
}

