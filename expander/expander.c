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
	(void)new_head;
	ft_expand_var(head, env);
	char **output;
	output = ft_split_last_cmd(head->value);
	if (!output || !output[0])
	{
		token_node *new = addnew_tkn_node(VAR, NULL, head->fd_hrd);
		new->flage = true;
		lstadd_back(new_head, new);
	}
	if (head->value && (head->value[0] == '\t' || head->value[0] == ' '))
	{
		token_node *new = addnew_tkn_node(SPC, ft_strdup(" "), -2);
		lstadd_back(new_head, new);
	}
	int i = 0;
	token_node *tmp = NULL;
	while (output && output[i])
	{
		token_node *new = addnew_tkn_node(VAR, output[i], -2);
		lstadd_back(new_head, new);
		if (!tmp)
			tmp = new;
		if (output[i + 1])
			lstadd_back(new_head, addnew_tkn_node(SPC, " ", -2));
		i++;
	}
	if (i > 1)
		tmp->flage = true;
	// if (!output[0])
	// {
	// 	puts("OK");
	// 	token_node *new = addnew_tkn_node(VAR, ft_strdup(""), head->fd_hrd);
	// 	new->flage = true;
	// 	lstadd_back(new_head, new);
	// }
}
char *expand_str_vars(token_node *head, t_expand *env, int exit_status)
{
	size_t i;
	char *buffer;
	char *str_var;
	char *str_exp;
	char *str;

	buffer = NULL;
	i = 0;
	str = head->value;
	(void)exit_status;
	while (str[i])
	{
		str_var = get_until_var(str + i);
		if (!ft_strcmp(str_var, "$?"))
			str_exp = ft_itoa(exit_status);
		else
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
token_node *expand_and_print_vars(token_node *head, t_expand *env, int exit_status)
{
	char *buffer;
	token_node *new_head;

	buffer = NULL;
	new_head = NULL;
	while (head)
	{
		if (head->type == EXIT_STATUS)
		{
			head->value = ft_itoa(exit_status);
			head->type = STRING;
		}
		if (head->type == VAR)
		{
			expand_var_and_split(&new_head, head, env);
			head = head->next;
		}
		else if (head->type == DOUBLE_Q)
		{
			buffer = expand_str_vars(head, env, exit_status);
			head->value = buffer;
		}
		if (head && head->type != VAR)
		{
			lstadd_back(&new_head, addnew_tkn_node(head->type, head->value, head->fd_hrd));
			head = head->next;
		}
	}
	return (new_head);
}
