/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:53:18 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/30 22:59:14 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars_key(char *cmd)
{
	int i;

	i = 0;
	if (!cmd || !*cmd)
	{
		perror("invalid option");
		return (1);
	}
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_') && !ft_isdigit(cmd[0]))
		i++;
	if (cmd[i])
	{
		perror("invalid option");
		return (1);
	}
	return (0);
}

void	ft_export_exicted(t_expand *node, t_expand **envp)
{
	t_expand *head;

	head = *envp;
	while (head)
	{
		if (ft_strcmp(node->key, head->key) == 0)
		{
			if (node->value && *(node->value))
				head->value = ft_strdup(node->value);
			ft_free_node(node);
			return ;
		}
		head = head->next;
	}
	ft_lst_add_back(envp , node);
}

void	ft_export(char **cmd, t_expand **envp)
{
	t_expand	*new;
	char		*key;
	char		*value;
	int			i;
	int			j;

	i = 0;
	j = 0;
	value = NULL;
	if (!cmd[1])
	{
		ft_env(cmd, *envp);
		return ;
	}
	while(cmd[++j])
	{
		i = 0;
		while(cmd[j][i] && cmd[j][i] != '=')
			i++;
		key = ft_substr(cmd[j], 0, i);
		if(pars_key(key))
			return ;
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
			return ;
		ft_export_exicted(new, envp);
	}
}

// int main()
// {
// 	t_expand *envp = NULL;
	
// 	ft_lst_add_back(&envp, ft_lst_new(ft_strdup("var1"), ft_strdup("jkanf")));
// 	ft_lst_add_back(&envp, ft_lst_new("var2", "jkanf"));
// 	ft_lst_add_back(&envp, ft_lst_new("var3", "jkanf"));
// 	ft_lst_add_back(&envp, ft_lst_new("var5", "jkanf"));

// 	char *cmd[] = {"export","bdjs=","aafsa", "saafsa=hjdbv", NULL};
// 	ft_export(cmd, &envp);
// 	ft_env(cmd, envp);
// 	// char *cmd2[] = {"export","var1", NULL};
// 	// //ft_unset(cmd2, &envp);
// 	// ft_env(cmd, envp);
// }