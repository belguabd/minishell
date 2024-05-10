/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:34:47 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 08:41:49 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	checkn(char **cmd)
{
	int	i;
	int	j;
	int	checkn;

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
	int	n;

	n = checkn(cmd);
	i = n + 1;
	if (cmd[i])
		ft_putstr_fd(cmd[i++], 1);
	while (cmd[i])
	{
		if (cmd[i])
		{
			write(1, " ", 1);
			ft_putstr_fd(cmd[i++], 1);
		}
	}
	if (n == 0)
		write(1, "\n", 1);
}
