/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 04:15:27 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/11 09:59:44 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_red(t_cmd *cmd, int *exit_status)
{
	if (cmd->infile != 0)
	{
		if (cmd->infile < 0)
			*exit_status = 1;
		if ((dup2(cmd->infile, 0) < 0))
			return (1);
		close(cmd->infile);
	}
	if (cmd->outfile != 1)
	{
		if (cmd->outfile < 0)
			*exit_status = 1;
		if ((dup2(cmd->outfile, 1) < 0))
			return (1);
		close(cmd->outfile);
	}
	return (0);
}

int	exe_one_cmd_only(t_cmd *cmd, t_expand **env, int *exit_status)
{
	int	save_in;
	int	save_out;

	if (cmd->isfirst && cmd->islast && is_builtin(cmd))
	{
		save_in = dup(0);
		save_out = dup(1);
		if (save_in < 0 || save_out < 0)
			ft_putendl_fd("dup error", 2);
		if (ft_red(cmd, exit_status) == 1)
			return (1);
		if (!exe_bultin_in_parent(cmd->args, env, exit_status))
			return (0);
		if ((dup2(save_in, 0) < 0))
			close(0);
		close(save_in);
		if ((dup2(save_out, 1) < 0))
			close(1);
		close(save_out);
		return (1);
	}
	return (0);
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (0);
	if ((ft_strcmp(cmd->args[0], "echo") == 0)
		|| (ft_strcmp(cmd->args[0], "export") == 0)
		|| (ft_strcmp(cmd->args[0], "env") == 0)
		|| (ft_strcmp(cmd->args[0], "cd") == 0)
		|| (ft_strcmp(cmd->args[0], "pwd") == 0)
		|| (ft_strcmp(cmd->args[0], "unset") == 0)
		|| (ft_strcmp(cmd->args[0], "exit") == 0))
		return (1);
	return (0);
}

int	exe_part2(char *cmd[], t_expand **env, int *exit_status)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_env(cmd, *env), *exit_status = 0, 1);
	else if (ft_strcmp(cmd[0], "cd") == 0)
	{
		*exit_status = ft_cd(cmd[1], *env);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_pwd(*env), *exit_status = 0, 1);
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		*exit_status = ft_unset(cmd, env);
		return (1);
	}
	return (0);
}

int	exe_bultin_in_parent(char *cmd[], t_expand **env, int *exit_status)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
	{
		*exit_status = 0;
		return (ft_echo(cmd), 1);
	}
	else if (ft_strcmp(cmd[0], "exit") == 0)
	{
		*exit_status = ft_exit(cmd, *exit_status);
		return (1);
	}
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		*exit_status = ft_export(cmd, env);
		return (1);
	}
	if (exe_part2(cmd, env, exit_status) == 1)
		return (1);
	return (0);
}
