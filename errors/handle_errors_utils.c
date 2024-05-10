/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:17:31 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:46:15 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quote_error_handling(const char *buffer, size_t *i, char c)
{
	while (buffer[(*i)] && buffer[(*i)] != c)
		(*i)++;
	if (buffer[(*i)] && buffer[(*i)] == c)
		return (0);
	else
	{
		ft_putendl_fd("close quote", 2);
		return (-1);
	}
	return (0);
}

int	print_error_quote(const char *cmd)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(cmd);
	while (i < len)
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i++;
			if (quote_error_handling(cmd, &i, cmd[i - 1]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
