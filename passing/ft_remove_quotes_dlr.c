/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes_dlr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:21:50 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/09 03:23:04 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

token_node *skip_dr(token_node *head)
{
	token_node	*new_head;
	token_node	*new_node;

	new_head = NULL;
	while (head)
	{
		if (head->type == STRING && !head->value)
		{
			head = head->next;
			continue;
		}
		new_node = addnew_tkn_node(head->type, head->value, head->fd_hrd);
		if (head->flag)
			new_node->flag = true;
		lstadd_back(&new_head, new_node);
		head = head->next;
	}
	return (new_head);
}
void	rm_sgl_q(token_node *head)
{
	while (head)
	{
		if (head->type == SINGLE_Q)
			head->value = ft_strtrim(head->value, "\'");
		head = head->next;
	}
}

void	rm_dbl_q(token_node *head)
{
	while (head)
	{
		if (head->type == DOUBLE_Q)
			head->value = ft_strtrim(head->value, "\"");
		head = head->next;
	}
}