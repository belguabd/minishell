/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:39:31 by belguabd          #+#    #+#             */
/*   Updated: 2024/04/25 16:53:56 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_atoi(const char *str)
{

	int sign;
	size_t res;
	int i;

	i = 0;
	sign = 1;
	res = 0;
	while (((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - 48) + (res * 10);
		if (res > LONG_MAX)
		{
			printf("exit\n");
			printf("minishell: exit: %zu: numeric argument required\n", res);
			exit(255);
		}
		i++;
	}
	return (res * sign);
}

bool check_is_digit(char *nbr)
{
	int i;
	
	i = 0;
	if(!nbr) //add this bcz there is a seg fault in the case (exit '')
		return (false);
	if (nbr[i] == '-' || nbr[i] == '+')
		i++;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (false);
		i++;
	}
	return (true);
}

void ft_exit(char **cmd)
{
	if (cmd[1])
	{
		char **output = ft_split_last_cmd(cmd[1]);
		if (!check_is_digit(output[0]))
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			exit(255);
		}
		if (cmd[2])
		{
			printf("exit\n");
			printf("minishell: exit: too many arguments\n");
		}
		int i = ft_atoi(cmd[1]);
		int c = (char)i;
		exit(c);
	}
	else
		exit(0);
}