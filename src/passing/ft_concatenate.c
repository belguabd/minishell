/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concatenate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:08:59 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:43:04 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_string_type(int type)
{
	return (type == STRING
		|| type == SINGLE_Q
		|| type == DOUBLE_Q
		|| type == VAR
		|| type == DOUBLE_DLR
		|| type == EXIT_STATUS);
}

void	concat_string_flag_check(t_token_node **head, t_token_node **new)
{
	t_token_node	*new_node;
	bool			check;
	char			*buffer;

	check = false;
	buffer = NULL;
	while ((*head) != NULL && is_string_type((*head)->type))
	{
		if ((*head)->flag)
			check = true;
		buffer = ft_strjoin(buffer, (*head)->value);
		(*head) = (*head)->next;
	}
	new_node = addnew_tkn_node(STRING, buffer, -2);
	if (check)
	{
		new_node->flag = true;
		check = false;
	}
	lstadd_back(new, new_node);
}

t_token_node	*ft_concatenate(t_token_node *head)
{
	t_token_node	*new;

	new = NULL;
	while (head != NULL)
	{
		if (is_string_type(head->type))
			concat_string_flag_check(&head, &new);
		else
		{
			lstadd_back(&new, addnew_tkn_node(head->type,
					head->value, head->fd_hrd));
			head = head->next;
		}
	}
	return (new);
}
