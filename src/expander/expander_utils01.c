/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:20:05 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:42:37 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_str_env(t_expand *env, char *str_var)
{
	while (env && str_var)
	{
		if (!ft_strcmp(env->key, str_var))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*ft_get_var(char *str_var)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	if (str_var[i] >= '0' && str_var[i] <= '9')
		return (ft_substr(str_var, i, 1));
	while (str_var[i] && (ft_isalnum(str_var[i]) || str_var[i] == '_'))
		i++;
	return (ft_substr(str_var, start, i));
}

char	*get_until_var_exp(char *str_var)
{
	int	i;
	int	start;

	(1) && (i = 0, start = 0);
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
				break ;
			}
			while (str_var[i] && (ft_isalnum(str_var[i]) || str_var[i] == '_'))
				i++;
			break ;
		}
		i++;
	}
	return (ft_substr(str_var, start, i));
}
