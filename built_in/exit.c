/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:39:31 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/05 15:41:55 by belguabd         ###   ########.fr       */
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
			ft_putendl_fd("exit\nnumeric argument required\n", 2);
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
	if (!nbr) // add this bcz there is a seg fault in the case (exit '')
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

int ft_exit(char **cmd , int exit_status)
{
	if (cmd[1])
	{
		char **output = ft_split_last_cmd(cmd[1]);
		if (!check_is_digit(output[0])  || output[1])
		{
			ft_putendl_fd(": numeric argument required", 2);
			exit(255);
		}
		if (cmd[2])
		{
			ft_putendl_fd(": too many arguments", 2);
			return (1);
		}
		int i = ft_atoi(cmd[1]);
		
		int c = (char)i;
		write(2, "exit\n", 5);
		exit(c);
	}
	else
		exit(exit_status);
	return (0);
}
