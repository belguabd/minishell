/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:39:25 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/16 02:26:33 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd()
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) != NULL)
		printf("%s\n", path);
	else
		perror("pwd error");
}

