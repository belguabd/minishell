/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:44:40 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/02 09:48:21 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_del_node(t_expand **lst, char *key)
{
	t_expand 	*tmp;
	t_expand 	*head;
	t_expand	*prev;
	
	tmp = NULL;
	prev = NULL;
	head = *lst;
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
		{
			if (prev)
                prev->next = head->next;
			else 
                *lst = head->next;
			tmp = head;
			head = head->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = head;
		head = head->next;
	}
}

void	ft_unset(char **cmd, t_expand **envp)
{
	int	i;

	i = 1;
	if(!envp || !*envp)
		return ;
	while (cmd[i])
	{
		ft_del_node(envp, cmd[i]);
		i++;
	}
	return ;
}