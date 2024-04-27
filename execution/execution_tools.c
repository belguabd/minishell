/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 01:11:06 by soel-bou          #+#    #+#             */
/*   Updated: 2024/04/27 00:23:41 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_lst_size(t_expand *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
// int ft_strcmp(char *str1, char *str2)
// {
// 	int i = 0;

// 	while (str1[i] && str2[i] && str1[i] == str2[i])
// 		i++;
// 	return (str1[i] - str2[i]);
// }

void	set_cmd_false_true(t_cmd **cmds)
{
	t_cmd *cmd = *cmds;

	if(!cmds || !*cmds)
		return ;
	cmd->isfirst = true;
	cmd->islast = false;
	if(cmd->next)
	{
		cmd = cmd->next;
		while(cmd->next)
		{
			cmd->isfirst = false;
			cmd->islast = false;
			cmd = cmd->next;
		}
		if(!cmd->next)
		{
			cmd->isfirst = false;
			cmd->islast = true;
		}
	}
	else
		cmd->islast = true;
}
