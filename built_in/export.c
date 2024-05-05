/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:53:18 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/05 10:17:57 by belguabd         ###   ########.fr       */
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
		// perror("invalid option");
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (1);
	}
	len = ft_strlen(cmd);
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_') && !ft_isdigit(cmd[0]))
		i++;
	if (cmd[i])
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("': not a valid identifier", 2);
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
			if(head->value && *head->value)
				head->value = ft_strjoin_env(head->value, &node->value[2]);
			else if(!head->value[0])
				head->value = ft_strdup_env(&node->value[2]);
			return (1);
		}
		head = head->next;
	}
	node->value = ft_substr_env(node->value, 2, ft_strlen(node->value) - 1);
	lstadd_back_expand_env(envp, node);
	return (1);
}

void ft_export_exicted(t_expand *node, t_expand **envp, bool flag)
{
	t_expand *head;

	head = *envp;
	if(flag)
	{
		if((ft_join_value(node, envp)) == 1)
			return ;
	}
	while (head)
	{
		if (ft_strcmp(node->key, head->key) == 0)
		{
			if (!node->isnull)
			{
				head->value = ft_strdup_env(&node->value[0]);
				head->isnull = false;
			}
			return;
		}
		head = head->next;
	}
	lstadd_back_expand_env(envp, node);
}

int ft_export(char **cmd, t_expand **envp)
{
	t_expand *new;
	char *key;
	char *value;
	bool isnull;
	bool flag;
	int exit_status;
	int i;
	int j;

	i = 0;
	j = 0;
	exit_status = 0;
	value = NULL;
	if (!cmd[1])
	{
		get_env_export(*envp);
		return (0);
	}
	while (cmd[++j])
	{
		i = 0;
		flag = false;
		while (cmd[j][i] && (cmd[j][i] != '='))
		{
			if(cmd[j][i] == '+' && cmd[j][i + 1] == '=')
				break;
			i++;
		}
		key = ft_substr_env(cmd[j], 0, i);
		if (pars_key(key) == 0)
		{
			if (cmd[j][i])
			{
				if (cmd[j][i] == '=' && !cmd[j][i + 1])
				{
					isnull = false;
					value = ft_strdup_env("");
				}
				else if(cmd[j][i] == '+')
				{
					isnull = false;
					flag = true;
					value = ft_strdup_env(&cmd[j][i]);
				}
				else
				{
					isnull = false;
					value = ft_strdup_env(&cmd[j][i + 1]);
				}
			}
			else
			{
				value = ft_strdup_env("");
				isnull = true;
			}
			new = addnew_expand_node_env(key, value);
			if (!new)
				return (1);
			new->isnull = isnull;
			ft_export_exicted(new, envp, flag);
		}
		else
			exit_status = 1;
	}
	return (exit_status);
}
