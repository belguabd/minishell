/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 04:48:11 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 08:45:46 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*allocat_pids(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	int		*pids;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	pids = (int *)ft_malloc_env(i * sizeof(int), ALLOC);
	if (!pids)
	{
		ft_putendl_fd("malloc error", 2);
		exit(1);
	}
	return (pids);
}

void	init_fds(t_cmd **cmds)
{
	t_cmd			*head;
	t_token_node	*tmp;
	int				old_fd_in;
	int				old_fd_out;

	head = *cmds;
	while (head)
	{
		tmp = head->redir;
		old_fd_in = -2;
		old_fd_out = -2;
		if (tmp)
			redirection_loop(tmp, head);
		else
		{
			head->infile = 0;
			head->outfile = 1;
		}
		head = head->next;
	}
}
