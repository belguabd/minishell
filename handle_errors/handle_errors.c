/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 20:43:47 by belguabd          #+#    #+#             */
/*   Updated: 2024/04/03 00:35:35 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int quote_error_handling(const char *buffer, size_t *i, char c)
{
	while (buffer[(*i)] && buffer[(*i)] != c)
		(*i)++;
	if (buffer[(*i)] && buffer[(*i)] == c)
		return (0);
	else
	{
		ft_putendl_fd("close quote", 2);
		return (-1);
	}
	return (0);
}
int print_error_quote(const char *cmd)
{
	size_t i = 0;
	size_t len = ft_strlen(cmd);
	while (i < len)
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i++;
			if (quote_error_handling(cmd, &i, cmd[i - 1]) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
int print_error_redirection(token_node *head)
{
	token_node *tmp = head;
	while (tmp)
	{
		if (tmp->type >= REDIRECT_APPEND && tmp->type <= HEREDOC)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == SPC)
				tmp = tmp->next;
			if (tmp && tmp->type != STRING && tmp->type != DOUBLE_Q && tmp->type != SINGLE_Q && tmp->type != VAR && tmp->type !=DOUBLE_DLR)
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
int print_check_pip_start_line(token_node *head)
{
	token_node *tmp = head;
	tmp = head; // check pipe in line start
	if (tmp && tmp->type == SPC)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
	{
		ft_putendl_fd("syntax error near unexpected token", 2);
		return (-1);
	}
	return (0);
}
int print_error_double_pipe(token_node *head)
{
	token_node *tmp = head;
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
int handle_errors_cmd(token_node *head, const char *cmd)
{
	if(!head)
		return (-1);
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
