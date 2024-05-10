/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 02:43:38 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:45:37 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_sig_handler_her_doc(int sig)
{
	if (sig == SIGINT)
		close(0);
}

bool	ft_hr_dc_cntrl_c(t_token_node *head)
{
	t_token_node	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->fd_hrd == -3)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

char	*expand_heredoc(char *cmd, t_expand *env, int exit_status)
{
	char	*buffer;
	int		i;
	char	*str_var;
	char	*str_exp;

	i = 0;
	buffer = NULL;
	while (cmd[i])
	{
		str_var = get_until_var_exp(cmd + i);
		str_exp = ft_str_exp_double_q(str_var, env, exit_status);
		if (!buffer)
			buffer = ft_strdup("");
		buffer = ft_strjoin(buffer, str_exp);
		i += ft_strlen(str_var);
	}
	return (buffer);
}

int	write_to_file(char *buffer)
{
	char	*file_tmp;
	int		i;
	int		fd_read;
	int		fd;

	file_tmp = ft_strdup(".heredoc");
	i = 0;
	while (access(file_tmp, F_OK) != -1)
		file_tmp = ft_strjoin(".heredoc", ft_itoa(i++));
	fd = open(file_tmp, O_CREAT | O_RDWR | O_APPEND, 0777);
	fd_read = open(file_tmp, O_RDWR | O_APPEND, 0777);
	ft_close_fds(fd_read, OPEN);
	if (fd < 0)
		write(2, "Error\n", 6);
	if (fd_read < 0)
		write(2, "Error\n", 6);
	write(fd, buffer, ft_strlen(buffer));
	close(fd);
	unlink(file_tmp);
	return (fd_read);
}
