/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_redicrection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:15:10 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/09 03:16:28 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirection(int type)
{
	return (type == REDIRECT_APPEND
		|| type == REDIRECT_IN
		|| type == REDIRECT_OUT
		|| type == HEREDOC);
}

void	parse_redirection_token(token_node **head,
		token_node **new_node)
{
	token_node	*tmp;
	token_node	*new;
	int			type;
	char		*value;
	int			fd_hrd;

	tmp = NULL;
	type = (*head)->type;
	fd_hrd = (*head)->fd_hrd;
	tmp = (*head)->next;
	while (tmp && tmp->type == SPC)
	{
		(*head) = tmp;
		tmp = (*head)->next;
	}
	(*head) = tmp;
	value = (*head)->value;
	new = addnew_tkn_node(type, value, fd_hrd);
	if ((*head)->flag)
		new->flag = true;
	lstadd_back(new_node, new);
	(*head) = (*head)->next;
}

token_node	*rm_redirect(token_node *head)
{
	token_node	*new_node;

	new_node = NULL;
	while (head)
	{
		if (is_redirection(head->type))
			parse_redirection_token(&head, &new_node);
		else
		{
			lstadd_back(&new_node, addnew_tkn_node(head->type,
					head->value, -2));
			head = head->next;
		}
	}
	return (new_node);
}
