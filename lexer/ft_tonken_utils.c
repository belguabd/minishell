/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tonken_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:49:47 by belguabd          #+#    #+#             */
/*   Updated: 2024/04/17 09:17:42 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool is_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}
bool is_spaces(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return true;
	return false;
}
bool is_string(char c)
{
	return (c == '\"' || c == '\'' || c == '|' || c == '>' || c == '$' || c == '<' || is_spaces(c));
}
token_node *addnew_tkn_node(int token, char *value)
{
	token_node *new;
	new = (token_node *)ft_malloc(sizeof(token_node), ALLOC);
	if (!new)
		return (NULL);
	new->type = token;
	new->flage = false;
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}
void lstadd_back(token_node **lst, token_node *new)
{
	if (!*lst)
	{
		*lst = new;
		return;
	}
	token_node *cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}