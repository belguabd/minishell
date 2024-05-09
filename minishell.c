/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/09 02:25:10 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig;

void ft_sig_handler_her_doc(int sig)
{
	if (sig == SIGINT)
		close(0);
}

void sig_handler(int sig)
{
	rl_catch_signals = 0;
	// add a variable to check if you are in line or in execution and check if the variable is 0 or no if 0 execute the if condition else don't
	if (sig == SIGINT)
	{
		write(1, "\n", 1); // Print a newline to ensure a new prompt starts on a new line
		rl_replace_line("", 0);
		rl_on_new_line(); // Reset readline's internal state
		rl_redisplay();
		g_sig = 1;
	}
}
void displayLinkedList(token_node *head)
{
	printf("\n+--------+-------+---------------+\n");
	printf("|fd |     Value     |\n");
	printf("+--------+-------+---------------+\n");

	int index = 0;
	while (head != NULL)
	{
		printf("|%7d|%7d | %-14s|\n", head->fd_hrd, head->type, head->value);
		head = head->next;
		index++;
	}
	printf("+--------+-------+---------------+\n");
}

int ft_strcmp(char *str1, char *str2)
{
	int i = 0;

	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
void display_expand_list(t_expand *head)
{
	t_expand *current = head;

	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void rm_sgl_q(token_node *head)
{
	while (head)
	{
		if (head->type == SINGLE_Q)
			head->value = ft_strtrim(head->value, "\'");
		head = head->next;
	}
}
void rm_dbl_q(token_node *head)
{
	while (head)
	{
		if (head->type == DOUBLE_Q)
			head->value = ft_strtrim(head->value, "\"");
		head = head->next;
	}
}

int is_string_type(int type)
{
	return (type == STRING || type == SINGLE_Q || type == DOUBLE_Q || type == VAR || type == DOUBLE_DLR || type == EXIT_STATUS);
}
/*start heredoc*/
// ---------------
bool ft_hr_dc_cntrl_c(token_node *head)
{
	token_node *tmp = head;
	while (tmp)
	{
		if (tmp->fd_hrd == -3)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
char *expand_heredoc(char *cmd, t_expand *env, int exit_status)
{
	char *buffer;
	int i;
	char *str_var;
	char *str_exp;

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

int write_to_file(char *buffer)
{
	char *file_tmp;
	int i;
	int fd_read;
	int fd;

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

char *append_cmd_to_buffer(char *cmd, char *buffer)
{
	if (!buffer)
		buffer = ft_strdup("");
	if (!cmd)
		cmd = ft_strdup("");
	buffer = ft_strjoin(buffer, cmd);
	buffer = ft_strjoin(buffer, ft_strdup("\n"));
	return (buffer);
}
// ----------------
int ft_readline(int flag, char *dlmtr, t_expand *env, int *exit_status)
{
	char *buffer;
	char *cmd;
	char *free_cmd;

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
			break;
		}
		if (flag != 1337)
			cmd = expand_heredoc(cmd, env, *exit_status);
		buffer = append_cmd_to_buffer(cmd, buffer);
		free(free_cmd);
	}
	return (write_to_file(buffer));
}

int readline_hdc(char *dlmtr, t_expand *env, int flag, int *exit_status)
{
	char *buffer;

	buffer = NULL;
	return (ft_readline(flag, dlmtr, env, exit_status));
}

char *process_next_string(token_node **head, int *flag)
{
	token_node *tmp;
	char *buffer;

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

void ft_heredoc(token_node *head, t_expand *env, int *exit_status)
{
	char *buffer;
	int flag;

	flag = 0;
	buffer = NULL;
	while (head)
	{
		if (head->type == HEREDOC)
		{
			buffer = process_next_string(&head, &flag);
			if (!buffer)
				return;
			head->fd_hrd = readline_hdc(buffer, env, flag, exit_status);
			if (head->fd_hrd == -3)
			{
				*exit_status = 1;
				head->fd_hrd = -3;
				return;
			}
			buffer = NULL;
		}
		head = head->next;
	}
}
/*end heredoc*/
void concat_string_flag_check(token_node **head, token_node **new)
{
	token_node *new_node;
	bool check;
	char *buffer;

	check = false;
	buffer = NULL;
	while ((*head) != NULL && is_string_type((*head)->type))
	{
		if ((*head)->flag)
			check = true;
		buffer = ft_strjoin(buffer, (*head)->value);
		(*head) = (*head)->next;
	}
	new_node = addnew_tkn_node(STRING, buffer, -2);
	if (check)
	{
		new_node->flag = true;
		check = false;
	}
	lstadd_back(new, new_node);
}

token_node *ft_concatenate(token_node *head)
{
	token_node *new;

	new = NULL;
	while (head != NULL)
	{
		if (is_string_type(head->type))
			concat_string_flag_check(&head, &new);
		else
		{
			lstadd_back(&new, addnew_tkn_node(head->type,
											  head->value, head->fd_hrd));
			head = head->next;
		}
	}
	return (new);
}
/*start remove redirection*/
bool is_redirection(int type)
{
	return (type == REDIRECT_APPEND || type == REDIRECT_IN || type == REDIRECT_OUT || type == HEREDOC);
}
void parse_redirection_token(token_node **head,
							 token_node **new_node)
{
	token_node *tmp;
	token_node *new;
	int type;
	char *value;
	int fd_hrd;

	tmp = NULL;
	type = (*head)->type;
	fd_hrd = (*head)->fd_hrd;
	tmp = (*head)->next;
	while (tmp && tmp->type == SPC)
	{
		(*head) = tmp;
		tmp = (*head)->next;
	}
	(*head) = tmp;
	value = (*head)->value;
	new = addnew_tkn_node(type, value, fd_hrd);
	if ((*head)->flag)
		new->flag = true;
	lstadd_back(new_node, new);
	(*head) = (*head)->next;
}

token_node *rm_redirect(token_node *head)
{
	token_node *new_node;

	new_node = NULL;
	while (head)
	{
		if (is_redirection(head->type))
			parse_redirection_token(&head, &new_node);
		else
		{
			lstadd_back(&new_node, addnew_tkn_node(head->type,
												   head->value, -2));
			head = head->next;
		}
	}
	return (new_node);
}
/*end remove redirection*/
/*start ft_passing*/
void lst_addback_cmd(t_cmd **lst_cmd, t_cmd *new_cmd)
{
	t_cmd *tmp;

	tmp = *lst_cmd;
	if (!tmp)
	{
		*lst_cmd = new_cmd;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

t_cmd *addnew_cmd(char **args, token_node *head_cmd)
{
	t_cmd *new_cmd;

	new_cmd = (t_cmd *)ft_malloc(sizeof(t_cmd), ALLOC);
	if (!new_cmd)
		return (NULL);
	new_cmd->args = args;
	new_cmd->redir = head_cmd;
	new_cmd->infile = 0;
	new_cmd->outfile = 1;
	new_cmd->next = NULL;
	return (new_cmd);
}

void parse_arguments_redirects(token_node *new_head,
							   char **args, token_node **redir)
{
	token_node *new;
	int i;

	i = 0;
	while (new_head)
	{
		if (new_head->type == STRING)
			args[i++] = ft_strdup(new_head->value);
		if (is_redirection(new_head->type))
		{
			new = addnew_tkn_node(new_head->type, new_head->value,
								  new_head->fd_hrd);
			if (new_head->flag)
				new->flag = true;
			lstadd_back(redir, new);
		}
		new_head = new_head->next;
	}
	args[i] = NULL;
}

t_cmd *ft_split_cmd(token_node *new_head)
{
	token_node *tmp;
	token_node *redir;
	int count;
	char **args;

	count = 0;
	tmp = new_head;
	redir = NULL;
	while (tmp)
	{
		if (tmp->type == STRING)
			count++;
		tmp = tmp->next;
	}
	args = (char **)ft_malloc(sizeof(char *) * (count + 1), ALLOC);
	parse_arguments_redirects(new_head, args, &redir);
	return (addnew_cmd(args, redir));
}

t_cmd *passing(token_node *head)
{
	t_cmd *new_cmd;
	token_node *new_head;
	token_node *new_node;

	new_cmd = NULL;
	while (head)
	{
		new_head = NULL;
		while (head)
		{
			if (head->type == PIPE)
				break;
			new_node = addnew_tkn_node(head->type, head->value, head->fd_hrd);
			if (head->flag)
				new_node->flag = true;
			lstadd_back(&new_head, new_node);
			head = head->next;
		}
		lst_addback_cmd(&new_cmd, ft_split_cmd(new_head));
		if (head)
			head = head->next;
	}
	return (new_cmd);
}
/*end ft_passing*/

void ll()
{
	system("leaks minishell");
}
token_node *skip_dr(token_node *head)
{
	token_node *new_head;
	token_node *new_node;

	new_head = NULL;
	while (head)
	{
		if (head->type == STRING && !head->value)
		{
			head = head->next;
			continue;
		}
		new_node = addnew_tkn_node(head->type, head->value, head->fd_hrd);
		if (head->flag)
			new_node->flag = true;
		lstadd_back(&new_head, new_node);
		head = head->next;
	}
	return (new_head);
}
void shell_signal_read(const char **cmd, int *exit_st)
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
		exit(0);
	}
	if (*cmd[0])
		add_history(*cmd);
}
void clean_exit(const char *cmd, int *exit_st)
{
	*exit_st = 258;
	free((void *)cmd);
	ft_malloc(FREE, FREE);
	ft_close_fds(FREE, CLOSE);
}
void clean_fd_cmd(const char *cmd)
{
	free((void *)cmd);
	ft_malloc(FREE, FREE);
	ft_close_fds(FREE, CLOSE);
}
void process_shell_input(token_node **head, const char **cmd,
						 int *exit_st, t_expand *env_e)
{
	shell_signal_read(cmd, exit_st);
	(*head) = tokenization(*cmd, head);
	rm_sgl_q((*head));
	rm_dbl_q((*head));
	ft_heredoc((*head), env_e, exit_st);
}
int main(int ac, char const *av[], char *env[])
{
	const char *cmd;
	token_node *head;
	t_expand *env_e;
	int exit_st;

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
