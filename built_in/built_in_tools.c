/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:57:58 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/19 22:45:21 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_expand	*ft_lstlast(t_expand *lst)
{
	t_expand	*last;

	last = lst;
	while (last->next)
	{
		last = last->next;
	}
	return (last);
}

void	ft_lst_add_back(t_expand **lst, t_expand *new_node)
{
	t_expand	*last;

	last = ft_lstlast(*lst);
	if (!last)
		*lst = new_node;
	else
		last->next = new_node;
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	ft_del_node(t_expand **lst, char *key)
{
	t_expand *tmp;
	t_expand *head;
	
	tmp = NULL;
	head = *lst;
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			tmp = head;
			head = head->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		head = head->next;
	}
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