/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:12:43 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/30 12:41:21 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_env(char **cmd, t_expand *envp)
{
	(void)cmd;
	t_expand *head;

	if(!envp)
	{
		ft_putstr_fd("env: No such file or directory\n", 2);
		return ;
	}
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
void ft_sort_export(t_expand *head)
{
	char *value;
	char *key;
	while (head)
	{
		t_expand *tmp = head->next;
		while (tmp)
		{
			if (strcmp(head->key, tmp->key) > 0)
			{
				key = head->key;
				head->key = tmp->key;
				tmp->key = key;
				value = head->value;
				head->value = tmp->value;
				tmp->value = value;
			}
			tmp = tmp->next;
		}
		head = head->next;
	}
}

void get_env_export(t_expand *envp)
{
	t_expand *head;

	if (!envp)
		return ;
	head = envp;
	//ft_sort_export(head);
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