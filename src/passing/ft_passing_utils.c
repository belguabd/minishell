/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_passing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 02:18:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/11 07:33:50 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_new_redir(t_token_node **new, t_token_node *new_head,
		t_token_node **redir)
{
	(*new) = addnew_tkn_node(new_head->type, new_head->value,
			new_head->fd_hrd);
	if (new_head->flag)
		(*new)->flag = true;
	lstadd_back(redir, *new);
}

t_cmd	*ft_split_cmd(t_token_node *new_head)
{
	t_token_node	*tmp;
	t_token_node	*new;
	t_token_node	*redir;
	char			**args;
	int				i;

	tmp = new_head;
	redir = NULL;
	args = (char **)ft_malloc(sizeof(char *) * (ft_count_cmd(tmp) + 1),
			ALLOC);
	if (!args)
		return (NULL);
	i = 0;
	while (new_head)
	{
		if (new_head->type == STRING)
			args[i++] = ft_strdup(new_head->value);
		if (is_redirection(new_head->type))
			add_new_redir(&new, new_head, &redir);
		new_head = new_head->next;
	}
	return (args[i] = NULL, addnew_cmd(args, redir));
}
