/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:20:05 by belguabd          #+#    #+#             */
/*   Updated: 2024/04/19 06:04:54 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_string_exp(char *str, char *old_var, char *new_var)
{
	size_t len = (ft_strlen(str) - (ft_strlen(old_var))) + ft_strlen(new_var);
	if (ft_strlen(old_var))
		len++;
	char *new = (char *)ft_malloc(len + 1, ALLOC);
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
char *get_var_odd(char *str_var, t_expand *env)
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
	size_t i;
	char *str_exp;
	char *get_var;
	size_t len;
	size_t count;

	str_exp = NULL;
	get_var = NULL;
	len = ft_strlen(str_var);
	i = 0;
	while (i < len)
	{
		if (str_var[i] == '$')
		{
			count = i;
			while (str_var[i] && str_var[i] == '$')
				i++;
			count = i - count;
			if (count % 2 != 0)
				str_exp = get_var_odd(str_var + i, env);
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

	char *str;
	int i;
	size_t len;

	i = 1;
	str = head->value;
	len = ft_strlen(str);
	if (len == 1)
		head->value = ft_strdup("$");
	else
	{
		char *var = get_str_env(env, str + i);
		head->value = var;
	}
}
void expand_var_and_split(token_node **new_head, token_node *head, t_expand *env)
{
	ft_expand_var(head, env);
	char **output;
	int i;

	output = ft_split_last_cmd(head->value);
	i = 0;
	while (output[i])
	{
		lstadd_back(new_head, addnew_tkn_node(VAR, output[i]));
		if (output[i + 1])
			lstadd_back(new_head, addnew_tkn_node(SPC, " "));
		i++;
	}
}
char *expand_str_vars(token_node *head, t_expand *env)
{
	size_t i;
	char *buffer;
	char *str_var;
	char *str_exp;
	char *str;

	buffer = NULL;
	i = 0;
	str = head->value;
	while (str[i])
	{
		str_var = get_until_var(str + i);
		str_exp = ft_str_exp(str_var, env);
		if (!buffer)
			buffer = ft_strdup("");
		buffer = ft_strjoin(buffer, str_exp);
		i += ft_strlen(str_var);
	}
	if (!buffer)
		buffer = ft_strdup("");
	return (buffer);
}
token_node *expand_and_print_vars(token_node *head, t_expand *env)
{
	char *buffer;
	token_node *new_head;

	buffer = NULL;
	new_head = NULL;
	while (head)
	{
		if (head->type == VAR)
		{
			expand_var_and_split(&new_head, head, env);
			head = head->next;
		}
		else if (head->type == DOUBLE_Q)
		{
			buffer = expand_str_vars(head, env);
			head->value = buffer;
		}
		if (head && head->type != VAR)
		{
			lstadd_back(&new_head, addnew_tkn_node(head->type, head->value));
			head = head->next;
		}
	}
	return (new_head);
}
