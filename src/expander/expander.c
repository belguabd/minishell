/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:20:05 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 09:09:19 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_expand_var(t_token_node *head, t_expand *env)
{
	char	*str;
	int		i;
	size_t	len;
	char	*var;

	i = 1;
	str = head->value;
	len = ft_strlen(str);
	if (len == 1)
		head->value = ft_strdup("$");
	else
	{
		var = get_str_env(env, str + i);
		head->value = var;
	}
}

void	tokenize_and_add_to_list(char **output, t_token_node **new_head)
{
	t_token_node	*tmp;
	int				i;
	t_token_node	*new;

	i = 0;
	tmp = NULL;
	while (output && output[i])
	{
		new = addnew_tkn_node(VAR, output[i], -2);
		lstadd_back(new_head, new);
		if (!tmp)
			tmp = new;
		if (output[i + 1])
			lstadd_back(new_head, addnew_tkn_node(SPC, " ", -2));
		i++;
	}
	if (tmp && i > 1)
		tmp->flag = true;
}

void	expand_var_and_split(t_token_node **new_head,
	t_token_node *head, t_expand *env)
{
	char			**output;
	t_token_node	*skip_space;
	t_token_node	*new;

	ft_expand_var(head, env);
	output = ft_split_last_cmd(head->value);
	if (!output || !output[0])
	{
		new = addnew_tkn_node(VAR, NULL, head->fd_hrd);
		new->flag = true;
		lstadd_back(new_head, new);
	}
	skip_space = ft_lstlast(*new_head);
	if ((skip_space && skip_space->value && skip_space->value[0])
		&& (head->value && (head->value[0] == '\t' || head->value[0] == ' ')))
	{
		new = addnew_tkn_node(SPC, ft_strdup(" "), -2);
		lstadd_back(new_head, new);
	}
	tokenize_and_add_to_list(output, new_head);
}

char	*expand_str_vars(t_token_node *head, t_expand *env, int exit_status)
{
	size_t	i;
	char	*buffer;
	char	*str_var;
	char	*str_exp;

	buffer = NULL;
	i = 0;
	while (head->value[i])
	{
		str_var = get_until_var_exp(head->value + i);
		str_exp = ft_str_exp_double_q(str_var, env, exit_status);
		if (!buffer)
			buffer = ft_strdup("");
		buffer = ft_strjoin(buffer, str_exp);
		i += ft_strlen(str_var);
	}
	if (!buffer)
		buffer = ft_strdup("");
	return (buffer);
}

t_token_node	*expand_and_print_vars(t_token_node *head,
	t_expand *env, int exit_status)
{
	t_token_node	*new_head;

	new_head = NULL;
	while (head)
	{
		if (head->type == EXIT_STATUS)
		{
			head->value = ft_itoa(exit_status);
			head->type = STRING;
			lstadd_back(&new_head, addnew_tkn_node(head->type,
					head->value, head->fd_hrd));
		}
		else if (head->type == VAR)
			expand_var_and_split(&new_head, head, env);
		else if (head->type == DOUBLE_Q)
			lstadd_back(&new_head, addnew_tkn_node(head->type,
					expand_str_vars(head, env, exit_status), head->fd_hrd));
		else
			lstadd_back(&new_head, addnew_tkn_node(head->type,
					head->value, head->fd_hrd));
		head = head->next;
	}
	return (new_head);
}
