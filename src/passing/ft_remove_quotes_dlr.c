/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes_dlr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:21:50 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:43:13 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token_node	*skip_dr(t_token_node *head)
{
	t_token_node	*new_head;
	t_token_node	*new_node;

	new_head = NULL;
	while (head)
	{
		if (head->type == STRING && !head->value)
		{
			head = head->next;
			continue ;
		}
		new_node = addnew_tkn_node(head->type, head->value, head->fd_hrd);
		if (head->flag)
			new_node->flag = true;
		lstadd_back(&new_head, new_node);
		head = head->next;
	}
	return (new_head);
}

void	rm_sgl_q(t_token_node *head)
{
	while (head)
	{
		if (head->type == SINGLE_Q)
			head->value = ft_strtrim(head->value, "\'");
		head = head->next;
	}
}

void	rm_dbl_q(t_token_node *head)
{
	while (head)
	{
		if (head->type == DOUBLE_Q)
			head->value = ft_strtrim(head->value, "\"");
		head = head->next;
	}
}
