/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:12:43 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/19 01:31:23 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **cmd, t_expand *envp)
{
	t_expand	*head;
	
	head = envp;
	while (head)
	{
		printf("%s=", head->key);
		printf("%s\n", head->value);
		head = head->next;
	}
}

int main()
{
	t_expand envp;
	t_expand envp1;
	t_expand envp2;
	t_expand envp3;

	envp.key = "HOME";
	envp.value = "test/test1";
	envp.next = &envp1;

	envp1.key = "HOME2";
	envp1.value = "test/test2";
	envp1.next = &envp2;

	envp2.key = "HOME3";
	envp2.value = "test/test3";
	envp2.next = &envp3;

	envp3.key = "HOME4";
	envp3.value = "test/test4";
	envp3.next = NULL;

	char **cmd;
	ft_env(cmd, &envp);
}