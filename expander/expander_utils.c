/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:20:05 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/26 22:32:17 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_get_var(char *str_var)
{
	int i = 0;
	int start = 0;
	if (str_var[i] >= '0' && str_var[i] <= '9')
		return (ft_substr(str_var, i, 1));
	while (str_var[i] && (ft_isalnum(str_var[i]) || str_var[i] == '_'))
		i++;
	return (ft_substr(str_var, start, i));
}
char *get_until_var(char *str_var)
{
	int i = 0;
	int start = 0;
	while (str_var[i])
	{
		if (str_var[i] == '$')
		{
			while (str_var[i] && str_var[i] == '$')
				i++;
			while (str_var[i] && (ft_isalnum(str_var[i]) || str_var[i] == '_'))
				i++;
			break;
		}
		i++;
	}
	return (ft_substr(str_var, start, i));
}