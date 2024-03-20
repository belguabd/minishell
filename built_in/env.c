/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:12:43 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/20 04:23:34 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **cmd, t_expand *envp)
{
	t_expand	*head;
	
	head = envp;
	while (head)
	{
		printf("%s", head->key);
		if(ft_strcmp(head->value, "\"\"") == 0)
			printf("=%s\n", head->value);
		else if(*(head->value))
			printf("=\"%s\"\n", head->value);
		else
			printf("\n");
		head = head->next;
	}
}

