/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:12:43 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/27 12:59:38 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **cmd, t_expand *envp)
{
	(void)cmd;
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

