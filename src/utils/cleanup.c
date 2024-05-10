/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 03:29:26 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:43:45 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clean_exit(const char *cmd, int *exit_st)
{
	*exit_st = 258;
	free((void *)cmd);
	ft_malloc(FREE, FREE);
	ft_close_fds(FREE, CLOSE);
}

void	clean_fd_cmd(const char *cmd)
{
	free((void *)cmd);
	ft_malloc(FREE, FREE);
	ft_close_fds(FREE, CLOSE);
}

void	process_shell_input(t_token_node **head, const char **cmd,
		int *exit_st, t_expand *env_e)
{
	shell_signal_read(cmd, exit_st);
	(*head) = tokenization(*cmd, head);
	rm_sgl_q((*head));
	rm_dbl_q((*head));
	ft_heredoc((*head), env_e, exit_st);
}
