/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:57:58 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/21 01:03:20 by soel-bou         ###   ########.fr       */
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

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if(!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}




t_expand	*ft_lst_new(char *key, char *val)
{
	t_expand *new;

	new = (t_expand*)malloc(sizeof(t_expand));
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
	free(node->value);
	free(node);
}