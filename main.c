/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/11 09:51:50 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	g_sig;

void	sig_handler(int sig)
{
	rl_catch_signals = 0;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig = 1;
	}
}

void	shell_signal_read(const char **cmd, int *exit_st)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, handler);
	*cmd = readline("➜ minishell ");
	if (g_sig == 1)
		*exit_st = 1;
	if (!*cmd)
	{
		ft_malloc(FREE, FREE);
		ft_malloc_env(FREE, FREE);
		ft_close_fds(FREE, CLOSE);
		write(1, "exit\n", 5);
		exit(*exit_st);
	}
	if (*cmd[0])
		add_history(*cmd);
}

int	main(int ac, char const *av[], char *env[])
{
	const char		*cmd;
	t_token_node	*head;
	t_expand		*env_e;
	int				exit_st;

	(1) && ((void)ac, (void)av, cmd = NULL, env_e = NULL);
	init_env(&env_e, env);
	rl_catch_signals = 0;
	while (1 && isatty(STDIN_FILENO))
	{
		head = NULL;
		process_shell_input(&head, &cmd, &exit_st, env_e);
		if (ft_hr_dc_cntrl_c(head))
			clean_fd_cmd(cmd);
		else if (handle_errors_cmd(head, cmd) == -1)
			clean_exit(cmd, &exit_st);
		else
		{
			head = expand_and_print_vars(head, env_e, exit_st);
			head = rm_redirect(ft_concatenate(head));
			ft_execution(passing(skip_dr(head)), &env_e, &exit_st);
			clean_fd_cmd(cmd);
		}
		g_sig = 0;
	}
}
