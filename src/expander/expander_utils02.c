/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils02.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:35:12 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:42:40 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '$')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (i);
}

char	*get_string_exp(char *str, char *new_var)
{
	char	*new;
	int		j;
	size_t	len;
	int		i;

	len = ft_strlen(str) + ft_strlen(new_var);
	new = (char *)ft_malloc(len + 1, ALLOC);
	i = ft_strcpy(new, str);
	while (str[i] && str[i] != '$')
	{
		new[i] = str[i];
		i++;
	}
	while (str[i] && str[i] == '$')
	{
		if (str[i + 1] != '$')
			break ;
		new[i] = str[i];
		i++;
	}
	j = 0;
	while (new_var && new_var[j])
		new[i++] = new_var[j++];
	return (new[i] = '\0', new);
}

char	*get_var_odd(char *str_var, t_expand *env)
{
	char	*get_var;
	char	*str_exp;

	get_var = NULL;
	str_exp = NULL;
	get_var = ft_get_var(str_var);
	if (get_var[0])
		str_exp = get_str_env(env, get_var);
	else
		str_exp = ft_strdup("$");
	return (str_exp);
}

char	*expand_string_variables(char *str_var, char *str_exp,
	int exit_status, t_expand *env)
{
	int	i;
	int	count;
	int	len;

	(1) && (i = -1, len = ft_strlen(str_var));
	while (++i < len)
	{
		if (str_var[i] == '$' && str_var[i + 1] == '?')
		{
			str_exp = ft_itoa(exit_status);
			break ;
		}
		if (str_var[i] == '$')
		{
			count = i;
			while (str_var[i] && str_var[i] == '$')
				i++;
			count = i - count;
			if (count % 2 != 0)
				str_exp = get_var_odd(str_var + i, env);
			else
				str_exp = ft_strjoin("$", ft_get_var(str_var + i));
		}
	}
	return (get_string_exp(str_var, str_exp));
}

char	*ft_str_exp_double_q(char *str_var, t_expand *env, int exit_status)
{
	char	*str_exp;

	str_exp = NULL;
	return (expand_string_variables(str_var, str_exp, exit_status, env));
}
