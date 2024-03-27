/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:20:05 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/26 22:32:14 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *get_string_exp(char *str, char *old_var, char *new_var)
{
	size_t len = (ft_strlen(str) - (ft_strlen(old_var))) + ft_strlen(new_var);
	if (ft_strlen(old_var))
		len++;
	char *new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	int i = 0;
	while (str[i] && str[i] != '$')
	{
		new[i] = str[i];
		i++;
	}
	while (str[i] && str[i] == '$')
	{
		if (str[i + 1] != '$')
			break;
		new[i] = str[i];
		i++;
	}
	int j = 0;
	if (new_var)
		while (new_var[j])
			new[i++] = new_var[j++];
	new[i] = '\0';
	return (new);
}
char *get_var_odd(char *str_var ,t_expand *env)
{
	char *get_var = NULL;
	char *str_exp = NULL;
	get_var = ft_get_var(str_var);
	if (get_var[0])
		str_exp = get_str_env(env, get_var);
	else
		str_exp = ft_strdup("$");
	return (str_exp);
}
char *ft_str_exp(char *str_var, t_expand *env)
{
	size_t i = 0;
	char *get_var = NULL;
	char *str_exp = NULL;
	size_t len = ft_strlen(str_var);
	while (i < len)
	{
		if (str_var[i] == '$')
		{
			size_t count = i;
			while (str_var[i] && str_var[i] == '$')
				i++;
			count = i - count;
			if (count % 2 != 0)
				str_exp = get_var_odd(str_var + i ,env);
			else
			{
				get_var = ft_get_var(str_var + i);
				get_var = ft_strjoin("$", get_var);
				str_exp = get_var;
			}
		}
		i++;
	}
	return (get_string_exp(str_var, get_var, str_exp));
}
void ft_expand_var(token_node *head, t_expand *env)
{
	char *buffer = NULL;
	int i = 0;
	char *str = head->value;
	int start = i;
	int end = 0;
	while (str[i] && str[i] == '$')
		i++;
	end = i - 1;
	if (str[i] >= '0' && str[i] <= '9')
		buffer = ft_strjoin(ft_substr(str, start, end), get_str_env(env, str + i));
	else
		buffer = ft_strjoin(ft_substr(str, start, end), get_str_env(env, str + i));
	free(head->value);
	head->value = buffer;
}
void expand_and_print_vars(token_node *head, t_expand *env)
{
	char *buffer;
	while (head)
	{
		if (head->type == VAR)
			ft_expand_var(head, env);
		else if (head->type == DOUBLE_Q)
		{
			buffer = NULL;
			size_t i = 0;
			char *str = head->value;
			while (str[i])
			{
				char *str_var = get_until_var(str + i);
				char *str_exp = ft_str_exp(str_var, env);
				if (!buffer)
					buffer = ft_strdup("");
				buffer = ft_strjoin(buffer, str_exp);
				i += ft_strlen(str_var);
			}
			head->value = buffer;
		}
		head = head->next;
	}
}
