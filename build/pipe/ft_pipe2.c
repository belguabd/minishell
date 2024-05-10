/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 04:49:59 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 08:45:44 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_get_exit_status(int *exit_status,
	int *pid, int i, struct termios *term)
{
	int	j;

	j = 0;
	while (j < i)
		waitpid(pid[j++], exit_status, 0);
	if (WIFSIGNALED(*exit_status) && WTERMSIG(*exit_status) == SIGQUIT)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, term);
		write(1, "Quit: 3\n", 8);
	}
	if (WIFSIGNALED(*exit_status) && WTERMSIG(*exit_status) == SIGINT)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, term);
		write(1, "\n", 1);
	}
	if (WIFEXITED(*exit_status))
		*exit_status = WEXITSTATUS(*exit_status);
	else if (WIFSIGNALED(*exit_status))
		*exit_status = WTERMSIG(*exit_status) + 128;
}

void	ft_cmd_redirection(t_cmd *cmd)
{
	if (cmd->infile != 0)
	{
		if (cmd->infile == -1)
			exit(1);
		if ((dup2(cmd->infile, 0) < 0))
			exit(1);
		close(cmd->infile);
	}
	if (cmd->outfile != 1)
	{
		if (cmd->outfile == -1)
			exit(1);
		if ((dup2(cmd->outfile, 1) < 0))
			close(1);
		close(cmd->outfile);
	}
}

void	ft_piping(t_cmd *cmd, int tmp_fd_in, int *fd)
{
	if (!cmd->isfirst)
	{
		dup2(tmp_fd_in, cmd->infile);
		close(tmp_fd_in);
	}
	if (!cmd->islast)
	{
		if (dup2(fd[1], cmd->outfile) < 0)
			close(cmd->outfile);
		close(fd[1]);
		close(fd[0]);
	}
}

void	ft_close_cmd_fd(t_cmd *cmd, int *tmp_fd_in, int *fd)
{
	if (!cmd->isfirst)
		close(*tmp_fd_in);
	if (!cmd->islast)
	{
		close(fd[1]);
		*tmp_fd_in = fd[0];
		if (*tmp_fd_in < 0)
			perror("tmp_fd_in");
	}
}
