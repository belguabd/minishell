/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:53:18 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 08:42:01 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_join_value(t_expand *node, t_expand **envp)
{
	t_expand	*head;

	head = *envp;
	while (head)
	{
		if (ft_strcmp(node->key, head->key) == 0)
		{
			if (head->value && *head->value)
				head->value = ft_strjoin_env(head->value, &node->value[2]);
			else if (!head->value[0])
				head->value = ft_strdup_env(&node->value[2]);
			head->isnull = false;
			return (1);
		}
		head = head->next;
	}
	node->value = ft_substr_env(node->value, 2, ft_strlen(node->value) - 1);
	lstadd_back_expand_env(envp, node);
	return (1);
}

void	ft_export_exicted(t_expand *node, t_expand **envp, bool flag)
{
	t_expand	*head;

	head = *envp;
	if (flag)
	{
		if ((ft_join_value(node, envp)) == 1)
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
			return ;
		}
		head = head->next;
	}
	lstadd_back_expand_env(envp, node);
}

void	ft_valid_key_case(t_export *var, char **cmd)
{
	if (cmd[var->j][var->i])
	{
		if (cmd[var->j][var->i] == '=' && !cmd[var->j][var->i + 1])
		{
			var->isnull = false;
			var->value = ft_strdup_env("");
		}
		else if (cmd[var->j][var->i] == '+')
		{
			var->isnull = false;
			var->flag = true;
			var->value = ft_strdup_env(&cmd[var->j][var->i]);
		}
		else
		{
			var->isnull = false;
			var->value = ft_strdup_env(&cmd[var->j][var->i + 1]);
		}
	}
	else
	{
		var->value = ft_strdup_env("");
		var->isnull = true;
	}
}

void	ft_get_key(t_export *var, char **cmd)
{
	var->i = 0;
	var->flag = false;
	while (cmd[var->j][var->i] && (cmd[var->j][var->i] != '='))
	{
		if (cmd[var->j][var->i] == '+' && cmd[var->j][var->i + 1] == '=')
			break ;
		var->i++;
	}
	var->key = ft_substr_env(cmd[var->j], 0, var->i);
}

int	ft_export(char **cmd, t_expand **envp)
{
	t_expand	*new;
	t_export	var;

	var.j = 0;
	var.exit_status = 0;
	var.value = NULL;
	if (!cmd[1])
		return (get_env_export(*envp), 0);
	while (cmd[++var.j])
	{
		ft_get_key(&var, cmd);
		if (pars_key(var.key) == 0)
		{
			ft_valid_key_case(&var, cmd);
			new = addnew_expand_node_env(var.key, var.value);
			if (!new)
				return (1);
			new->isnull = var.isnull;
			ft_export_exicted(new, envp, var.flag);
		}
		else
			var.exit_status = 1;
	}
	return (var.exit_status);
}
