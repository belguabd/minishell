/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:53:18 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/04 05:05:33 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int pars_key(char *cmd)
{
	int i;
	int len;

	i = 0;
	if (!cmd || !*cmd)
	{
		perror("invalid option");
		return (1);
	}
	len = ft_strlen(cmd);
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_') && !ft_isdigit(cmd[0]))
		i++;
	if (cmd[i])
	{
		perror("invalid option");
		return (1);
	}
	return (0);
}

int	ft_join_value(t_expand *node, t_expand **envp)
{
	t_expand *head;

	head = *envp;
	while(head)
	{
		if(ft_strcmp(node->key, head->key) == 0)
		{
			if(head->value && *head->value && ft_strcmp(head->value, "\"\""))
				head->value = ft_strjoin(head->value, &node->value[1]);
			else if(!head->value[0] || (ft_strcmp(head->value, "\"\"") == 0))
				head->value = ft_strdup(&node->value[1]);
			ft_free_node(node);
			return (1);
		}
		head = head->next;
	}
	node->value = ft_strdup(&node->value[1]);
	ft_lst_add_back(envp, node);
	return (1);
}

void ft_export_exicted(t_expand *node, t_expand **envp)
{
	t_expand *head;

	head = *envp;
	if(node->value[0] == '=')
	{
		if((ft_join_value(node, envp)) == 1)
			return ;		
	}
	while (head)
	{
		if (ft_strcmp(node->key, head->key) == 0)
		{
			if (node->value && *(node->value))
				head->value = ft_strdup(node->value);
			ft_free_node(node);
			return;
		}
		head = head->next;
	}
	ft_lst_add_back(envp, node);
}

void ft_export(char **cmd, t_expand **envp)
{
	t_expand *new;
	char *key;
	char *value;
	int i;
	int j;

	i = 0;
	j = 0;
	value = NULL;
	if (!cmd[1])
	{
		get_env_export(*envp);
		return;
	}
	while (cmd[++j])
	{
		i = 0;
		while (cmd[j][i] && (cmd[j][i] != '='))
		{
			if(cmd[j][i] == '+' && cmd[j][i + 1] == '=')
				break;
			i++;
		}
		key = ft_substr(cmd[j], 0, i);
		if (pars_key(key))
			return;
		if (cmd[j][i])
		{
			if (cmd[j][i] == '=' && !cmd[j][i + 1])
				value = ft_strdup("\"\"");
			else
				value = ft_strdup(&cmd[j][i + 1]);
		}
		else
			value = ft_strdup("");
		new = ft_lst_new(key, value);
		if (!new)
			return;
		ft_export_exicted(new, envp);
	}
}
