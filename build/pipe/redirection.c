/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 03:57:58 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 08:45:48 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	red_out(t_token_node *tmp, t_cmd *head)
{
	if (tmp->flag)
	{
		ft_putendl_fd("bash: ambiguous redirect", 2);
		head->outfile = -1;
		tmp->flag = false;
	}
	else
	{
		head->outfile = open(tmp->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (head->outfile > 2)
			ft_close_fds(head->outfile, OPEN);
		if (head->outfile < 0)
		{
			perror(tmp->value);
			return (1);
		}
	}
	return (0);
}

int	red_append(t_token_node *tmp, t_cmd *head)
{
	if (tmp->flag)
	{
		head->outfile = -1;
		ft_putendl_fd("bash: ambiguous redirect", 2);
		tmp->flag = false;
	}
	else
	{
		head->outfile = open(tmp->value, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (head->outfile > 2)
			ft_close_fds(head->outfile, OPEN);
		if (head->outfile < 0)
		{
			perror(tmp->value);
			return (1);
		}
	}
	return (0);
}

int	red_in(t_token_node *tmp, t_cmd *head)
{
	if (tmp->flag)
	{
		head->infile = -1;
		ft_putendl_fd("bash: ambiguous redirect", 2);
		tmp->flag = false;
	}
	else
	{
		head->infile = open(tmp->value, O_RDWR, 0644);
		if (head->infile > 2)
			ft_close_fds(head->infile, OPEN);
		if (head->infile < 0)
		{
			perror(tmp->value);
			return (1);
		}
	}
	return (0);
}

int	red_heredoc(t_token_node *tmp, t_cmd *head)
{
	head->infile = tmp->fd_hrd;
	if (head->infile < 0)
		return (1);
	return (0);
}

void	redirection_loop(t_token_node *tmp, t_cmd *head)
{
	while (tmp)
	{
		if (tmp->type == REDIRECT_OUT)
		{
			if (red_out(tmp, head) == 1)
				break ;
		}
		else if (tmp->type == REDIRECT_APPEND)
		{
			if (red_append(tmp, head) == 1)
				break ;
		}
		else if (tmp->type == REDIRECT_IN)
		{
			if (red_in(tmp, head) == 1)
				break ;
		}
		else if (tmp->type == HEREDOC)
		{
			if (red_heredoc(tmp, head) == 1)
				break ;
		}
		tmp = tmp->next;
	}
}
