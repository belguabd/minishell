/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:20:05 by belguabd          #+#    #+#             */
/*   Updated: 2024/04/30 14:46:19 by soel-bou         ###   ########.fr       */
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
			if (str_var[i] == '$' && str_var[i + 1] == '$')
				return (ft_substr(str_var, start, i + 2));
			if (str_var[i] == '$' && str_var[i + 1] == '?')
				return (ft_substr(str_var, start, i + 2));
			i++;
			if (str_var[i] >= '0' && str_var[i] <= '9')
			{
				i++;
				break;
			}
			while (str_var[i] && (ft_isalnum(str_var[i]) || str_var[i] == '_'))
				i++;
			break;
		}
		i++;
	}
	return (ft_substr(str_var, start, i));
}
char *get_until_var_exp(char *str_var)
{
	int i = 0;
	int start = 0;
	while (str_var[i])
	{
		if (str_var[i] == '$')
		{
			if (str_var[i] == '$' && str_var[i + 1] == '$')
				return (ft_substr(str_var, start, i + 2));
			if (str_var[i] == '$' && str_var[i + 1] == '?')
				return (ft_substr(str_var, start, i + 2));
			i++;
			if (str_var[i] >= '0' && str_var[i] <= '9')
			{
				i++;
				break;
			}
			while (str_var[i] && (ft_isalnum(str_var[i]) || str_var[i] == '_'))
				i++;
			break;
		}
		i++;
	}
	return (ft_substr(str_var, start, i));
}
