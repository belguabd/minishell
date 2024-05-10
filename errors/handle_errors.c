/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:43:47 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:46:21 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_print_syntax_error(void)
{
	ft_putendl_fd("syntax error near unexpected token", 2);
	return (-1);
}

int	print_error_redirection(t_token_node *head)
{
	t_token_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type >= REDIRECT_APPEND && tmp->type <= HEREDOC)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == SPC)
				tmp = tmp->next;
			if (tmp && tmp->type != STRING && tmp->type != DOUBLE_Q
				&& tmp->type != SINGLE_Q && tmp->type != VAR
				&& tmp->type != DOUBLE_DLR && tmp->type != EXIT_STATUS)
			{
				return (ft_print_syntax_error());
			}
			if (!tmp)
				return (ft_print_syntax_error());
		}
		tmp = tmp->next;
	}
	return (0);
}

int	print_check_pip_start_line(t_token_node *head)
{
	t_token_node	*tmp;

	tmp = head;
	if (tmp && tmp->type == SPC)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
	{
		ft_putendl_fd("syntax error near unexpected token", 2);
		return (-1);
	}
	return (0);
}

int	print_error_double_pipe(t_token_node *head)
{
	t_token_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == SPC)
				tmp = tmp->next;
			if (tmp && tmp->type == PIPE)
			{
				ft_putendl_fd("syntax error near unexpected token", 2);
				return (-1);
			}
			if (!tmp)
			{
				ft_putendl_fd("syntax error near unexpected token", 2);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	handle_errors_cmd(t_token_node *head, const char *cmd)
{
	if (print_error_quote(cmd) == -1)
		return (-1);
	if (print_error_redirection(head) == -1)
		return (-1);
	if (print_check_pip_start_line(head) == -1)
		return (-1);
	if (print_error_double_pipe(head) == -1)
		return (-1);
	return (0);
}
