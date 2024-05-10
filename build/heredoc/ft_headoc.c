/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_headoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 02:41:20 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:45:35 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*append_cmd_to_buffer(char *cmd, char *buffer)
{
	if (!buffer)
		buffer = ft_strdup("");
	if (!cmd)
		cmd = ft_strdup("");
	buffer = ft_strjoin(buffer, cmd);
	buffer = ft_strjoin(buffer, ft_strdup("\n"));
	return (buffer);
}

int	ft_readline(int flag, char *dlmtr, t_expand *env, int *exit_status)
{
	char	*buffer;
	char	*cmd;
	char	*free_cmd;

	buffer = NULL;
	signal(SIGINT, ft_sig_handler_her_doc);
	while (1)
	{
		cmd = readline("> ");
		free_cmd = cmd;
		if (!ttyname(0))
			return (free(free_cmd), open(ttyname(2), O_RDWR), -3);
		if (!cmd)
			return (write_to_file(buffer));
		if (!ft_strcmp(cmd, dlmtr))
		{
			free(free_cmd);
			break ;
		}
		if (flag != 1337)
			cmd = expand_heredoc(cmd, env, *exit_status);
		buffer = append_cmd_to_buffer(cmd, buffer);
		free(free_cmd);
	}
	return (write_to_file(buffer));
}

int	readline_hdc(char *dlmtr, t_expand *env, int flag, int *exit_status)
{
	char	*buffer;

	buffer = NULL;
	return (ft_readline(flag, dlmtr, env, exit_status));
}

char	*process_next_string(t_token_node **head, int *flag)
{
	t_token_node	*tmp;
	char			*buffer;

	buffer = NULL;
	tmp = (*head)->next;
	if (tmp && tmp->type == SPC)
		tmp = tmp->next;
	while (tmp && is_string_type(tmp->type))
	{
		if (!(*flag) && (tmp->type == SINGLE_Q || tmp->type == DOUBLE_Q))
			*flag = 1337;
		if (!buffer)
			buffer = ft_strdup("");
		buffer = ft_strjoin(buffer, tmp->value);
		tmp = tmp->next;
	}
	return (buffer);
}

void	ft_heredoc(t_token_node *head, t_expand *env, int *exit_status)
{
	char	*buffer;
	int		flag;

	flag = 0;
	buffer = NULL;
	while (head)
	{
		if (head->type == HEREDOC)
		{
			buffer = process_next_string(&head, &flag);
			if (!buffer)
				return ;
			head->fd_hrd = readline_hdc(buffer, env, flag, exit_status);
			if (head->fd_hrd == -3)
			{
				*exit_status = 1;
				head->fd_hrd = -3;
				return ;
			}
			buffer = NULL;
		}
		head = head->next;
	}
}
