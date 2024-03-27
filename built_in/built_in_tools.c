/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:57:58 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/27 20:40:06 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_lst_last(t_expand *lst)
{
	t_expand	*last;

	if (lst == NULL)
		return (NULL);
	last = lst;
	while (last && last->next)
	{
		last = last->next;
	}
	return (last);
}

void	ft_lst_add_back(t_expand **lst, t_expand *new_node)
{
	t_expand	*last;

	last = ft_lst_last(*lst);
	if (!last)
		*lst = new_node;
	else
		last->next = new_node;
}
t_expand	*ft_lst_new(char *key, char *val)
{
	t_expand *new;

	new = (t_expand*)ft_malloc(sizeof(t_expand) ,ALLOC);
	if (!new)
		return (NULL);
	new->key = key;
	new->value = val;
	new->next = NULL;
	return (new);
}

void	ft_free_node(t_expand *node)
{

	free(node->key);
	// node->key = NULL;
	free(node->value);
	// node->value = NULL;
	free(node);
	// node = NULL;
}