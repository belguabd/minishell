/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_passing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:01:33 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:43:11 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	lst_addback_cmd(t_cmd **lst_cmd, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = *lst_cmd;
	if (!tmp)
	{
		*lst_cmd = new_cmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

t_cmd	*addnew_cmd(char **args, t_token_node *head_cmd)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)ft_malloc(sizeof(t_cmd), ALLOC);
	if (!new_cmd)
		return (NULL);
	new_cmd->args = args;
	new_cmd->redir = head_cmd;
	new_cmd->infile = 0;
	new_cmd->outfile = 1;
	new_cmd->next = NULL;
	return (new_cmd);
}

int	ft_count_cmd(t_token_node *head)
{
	int	count;

	count = 0;
	while (head)
	{
		if (head->type == STRING)
			count++;
		head = head->next;
	}
	return (count);
}

t_cmd	*passing(t_token_node *head)
{
	t_token_node	*new_head;
	t_token_node	*new_node;
	t_cmd			*new_cmd;

	new_cmd = NULL;
	while (head)
	{
		new_head = NULL;
		while (head)
		{
			if (head->type == PIPE)
				break ;
			new_node = addnew_tkn_node(head->type, head->value, head->fd_hrd);
			if (head->flag)
				new_node->flag = true;
			lstadd_back(&new_head, new_node);
			head = head->next;
		}
		lst_addback_cmd(&new_cmd, ft_split_cmd(new_head));
		if (head)
			head = head->next;
	}
	return (new_cmd);
}
