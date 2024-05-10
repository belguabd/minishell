/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 23:19:52 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:44:20 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	size_t	get_len(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	size_t	i;
	long	num;
	char	*res;

	i = 0;
	len = get_len(n);
	res = (char *)ft_malloc(len + 1, ALLOC);
	if (!res)
		return (NULL);
	res[len] = '\0';
	num = n;
	if (num < 0)
	{
		res[0] = '-';
		num *= -1;
		i = 1;
	}
	while (len-- > i)
	{
		res[len] = (num % 10) + '0';
		num /= 10;
	}
	return (res);
}
