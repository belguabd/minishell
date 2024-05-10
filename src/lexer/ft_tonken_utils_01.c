/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tonken_utils_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:49:47 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:42:52 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

bool	is_spaces(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	is_string(char c)
{
	return (c == '\"' || c == '\'' || c == '|'
		|| c == '>' || c == '$' || c == '<' || is_spaces(c));
}

t_token_node	*addnew_tkn_node(int token, char *value, int fd)
{
	t_token_node	*new;

	new = (t_token_node *)ft_malloc(sizeof(t_token_node), ALLOC);
	if (!new)
		return (NULL);
	new->type = token;
	new->flag = false;
	new->value = value;
	new->fd_hrd = fd;
	new->next = NULL;
	return (new);
}

void	lstadd_back(t_token_node **lst, t_token_node *new)
{
	t_token_node	*cur;

	cur = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}
