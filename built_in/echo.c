/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:34:47 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/21 00:28:00 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int checkn(char **cmd)
{
	int i;
	int j;
	int checkn;

	i = 1;
	checkn = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && cmd[i][1] == 'n')
		{
			j = 2;
			while (cmd[i][j])
			{
				if (cmd[i][j] != 'n')
					return (checkn);
				j++;
			}
			checkn++;
		}
		else
			return (checkn);
		i++;
	}
	return (checkn);
}


void	ft_echo(char **cmd)
{
	int	i;
	int n;

	n = checkn(cmd);
	i = n + 1;
	if (cmd[i])
		printf("%s", cmd[i++]);
	while (cmd[i])
	{
		if (cmd[i])
			printf(" %s",cmd[i++]);
	}
	if (n == 0)
		printf("\n");
}
