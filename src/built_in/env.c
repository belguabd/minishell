/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:12:43 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 09:02:10 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(char **cmd, t_expand *envp)
{
	t_expand	*head;

	if (!envp)
	{
		ft_putstr_fd("env: No such file or directory\n", 2);
		return ;
	}
	if (cmd[1])
		return ;
	head = envp;
	while (head)
	{
		if (!head->isnull)
		{
			printf("%s", head->key);
			printf("=%s\n", head->value);
		}
		head = head->next;
	}
}

void	ft_swap(t_expand *head, t_expand *tmp)
{
	char		*value;
	char		*key;
	bool		isnull;

	key = head->key;
	value = head->value;
	isnull = head->isnull;
	head->key = tmp->key;
	head->value = tmp->value;
	head->isnull = tmp->isnull;
	tmp->key = key;
	tmp->value = value;
	tmp->isnull = isnull;
}

void	ft_sort_export(t_expand *head)
{
	t_expand	*tmp;

	while (head)
	{
		tmp = head->next;
		while (tmp)
		{
			if (ft_strcmp(head->key, tmp->key) > 0)
				ft_swap(head, tmp);
			tmp = tmp->next;
		}
		head = head->next;
	}
}

void	get_env_export(t_expand *envp)
{
	t_expand	*head;

	if (!envp)
		return ;
	head = envp;
	ft_sort_export(head);
	while (head)
	{
		printf("declare -x %s", head->key);
		if (!head->isnull)
			printf("=\"%s\"\n", head->value);
		else
			printf("\n");
		head = head->next;
	}
}
