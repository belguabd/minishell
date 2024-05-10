/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 02:07:02 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:45:25 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_all_env(t_free *head)
{
	t_free	*current;
	t_free	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->add);
		free(current);
		current = next;
	}
	head = NULL;
}

t_free	*addnew_free_env(void *add)
{
	t_free	*new;

	new = malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	new->add = add;
	new->next = NULL;
	return (new);
}

void	addback_free_env(t_free **head, t_free *new)
{
	t_free	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	*ft_malloc_env(size_t size, int status)
{
	static t_free	*head;
	void			*rt;
	t_free			*tmp;

	if (status == ALLOC)
	{
		rt = malloc(size);
		if (!rt)
			exit(0);
		tmp = addnew_free_env(rt);
		if (!tmp)
		{
			ft_free_all_env(head);
			exit(0);
		}
		addback_free_env(&head, tmp);
		return (rt);
	}
	else
		return (ft_free_all_env(head), head = NULL);
}

void	init_env(t_expand **head, char *env[])
{
	char	**cmd;
	int		i;
	int		j;
	char	*key;
	char	*value;

	cmd = ft_malloc(sizeof(char *) * 3, ALLOC);
	cmd[0] = ft_strdup_env("unset");
	cmd[1] = ft_strdup_env("OLDPWD");
	cmd[2] = NULL;
	i = -1;
	while (env[++i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		key = ft_substr_env(env[i], 0, j);
		value = ft_substr_env(env[i], j + 1, ft_strlen(env[i]) - j - 1);
		lstadd_back_expand_env(head, addnew_expand_node_env(key, value));
	}
	ft_unset(cmd, head);
	cmd[0] = ft_strdup_env("export");
	cmd[1] = ft_strdup("OLDPWD");
	cmd[2] = NULL;
	ft_export(cmd, head);
}
