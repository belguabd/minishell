/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 02:07:02 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/27 02:07:18 by belguabd         ###   ########.fr       */
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
	if (status == ALLOC)
	{
		void *rt = malloc(size);
		if (!rt)
			return (NULL);
		addback_free(&head, addnew_free(rt));
		return (rt);
	}
	else
		ft_free_all(head);
	return (NULL);
}