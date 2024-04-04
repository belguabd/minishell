/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 08:44:40 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/04 01:13:14 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pars_key_env(char *cmd)
{
	int i;
	int len;

	i = 0;
	if (!cmd || !*cmd)
		return (1);
	len = ft_strlen(cmd);
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_') && !ft_isdigit(cmd[0]))
		i++;
	if (cmd[i])
	{
		printf("bash: unset: `%s': not a valid identifier\n", cmd);
		return (1);
	}
	return (0);
}

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
		if(pars_key_env(cmd[i]))
			return ;
		ft_del_node(envp, cmd[i]);
		i++;
	}
	
	return ;
}