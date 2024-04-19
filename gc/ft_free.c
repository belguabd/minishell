/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 02:07:02 by belguabd          #+#    #+#             */
/*   Updated: 2024/04/19 01:40:34 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_free_all(t_free *head)
{
	t_free *current = head;
	while (current)
	{
		t_free *next = current->next;
		free(current->add);
		free(current);
		current = next;
	}
	head = NULL;
}

t_free *addnew_free(void *add)
{
	t_free *new = malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	new->add = add;
	new->next = NULL;
	return (new);
}
void addback_free(t_free **head, t_free *new)
{
	t_free *tmp = *head;
	if (!tmp)
	{
		*head = new;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
void *ft_malloc(size_t size, int status)
{
	static t_free *head = NULL;
	t_free	*tmp;
	if (status == ALLOC)
	{
		(void)size;
		void *rt = malloc(size);
		if (!rt)
			exit(0);
		tmp = addnew_free(rt);
		if (!tmp)
		{
			ft_free_all(head);
			exit(0);
		}
		addback_free(&head, tmp);
		return (rt);
	}
	else
		return (ft_free_all(head), head = NULL);
}
