/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:20:36 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 08:45:41 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_start_execution(t_cmd **cmd, t_expand **env_lst,
	int *exit_status, int *tmp_fd_in)
{
	*tmp_fd_in = -1;
	if (!*cmd)
		return (1);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	init_fds(cmd);
	if (exe_one_cmd_only(*cmd, env_lst, exit_status))
		return (1);
	return (0);
}

void	ft_child_exe(t_cmd *cmd, int tmp_fd_in, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	ft_cmd_redirection(cmd);
	ft_piping(cmd, tmp_fd_in, fd);
}

void	ft_fork_and_pipe(t_cmd *cmd, int *pid, int *fd)
{
	if (!cmd->islast)
		pipe(fd);
	*pid = fork();
	if (*pid < 0)
		perror("fork");
}

void	ft_close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	pipe_line(t_cmd *cmd, t_expand **env_lst, char *env[], int *exit_status)
{
	struct termios	term;
	int				fd[2];
	int				*pid;
	int				tmp_fd_in;
	int				i;

	i = 0;
	tcgetattr(STDIN_FILENO, &term);
	if (ft_start_execution(&cmd, env_lst, exit_status, &tmp_fd_in))
		return ;
	pid = allocat_pids(cmd);
	while (cmd)
	{
		ft_fork_and_pipe(cmd, &pid[i], fd);
		if (pid[i] == 0)
		{
			ft_child_exe(cmd, tmp_fd_in, fd);
			ft_execute_node(cmd->args, *env_lst, env, exit_status);
		}
		ft_close_cmd_fd(cmd, &tmp_fd_in, fd);
		cmd = cmd->next;
		i++;
	}
	ft_get_exit_status(exit_status, pid, i, &term);
	ft_close_pipe(fd);
}
