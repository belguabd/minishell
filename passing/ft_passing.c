/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_passing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:01:33 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/09 03:04:24 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_cmd	*addnew_cmd(char **args, token_node *head_cmd)
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

void	parse_arguments_redirects(token_node *new_head,
		char **args, token_node **redir)
{
	token_node	*new;
	int			i;

	i = 0;
	while (new_head)
	{
		if (new_head->type == STRING)
			args[i++] = ft_strdup(new_head->value);
		if (is_redirection(new_head->type))
		{
			new = addnew_tkn_node(new_head->type, new_head->value,
					new_head->fd_hrd);
			if (new_head->flag)
				new->flag = true;
			lstadd_back(redir, new);
		}
		new_head = new_head->next;
	}
	args[i] = NULL;
}

t_cmd	*ft_split_cmd(token_node *new_head)
{
	token_node	*tmp;
	token_node	*redir;
	int			count;
	char		**args;

	count = 0;
	tmp = new_head;
	redir = NULL;
	while (tmp)
	{
		if (tmp->type == STRING)
			count++;
		tmp = tmp->next;
	}
	args = (char **)ft_malloc(sizeof(char *) * (count + 1), ALLOC);
	parse_arguments_redirects(new_head, args, &redir);
	return (addnew_cmd(args, redir));
}

t_cmd	*passing(token_node *head)
{
	token_node	*new_head;
	token_node	*new_node;
	t_cmd		*new_cmd;

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
