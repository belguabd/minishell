/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/01 14:56:27 by soel-bou         ###   ########.fr       */
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
// t_expand *addnew_expand_node(char *key, char *value)
// {
// 	t_expand *new_node = (t_expand *)ft_malloc(sizeof(t_expand), ALLOC);
// 	if (!new_node)
// 		return NULL;

// 	new_node->key = ft_strdup(key);
// 	new_node->value = ft_strdup(value);
// 	new_node->next = NULL;
// 	return new_node;
// }

// void lstadd_back_expand(t_expand **lst, t_expand *new_node)
// {
// 	if (!*lst)
// 	{
// 		*lst = new_node;
// 		return;
// 	}
// 	t_expand *last = *lst;
// 	while (last->next)
// 		last = last->next;

// 	last->next = new_node;
// }
void display_expand_list(t_expand *head)
{
	t_expand *current = head;

	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

int get_var_len(const char *str, int i)
{
	int len = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (++len);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		len++;
		i++;
	}
	return (len);
}
char *get_str_env(t_expand *env, char *str_var)
{
	while (env && str_var)
	{
		if (!ft_strcmp(env->key, str_var))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void remove_single_q(token_node *head)
{
	while (head)
	{
		if (head->type == SINGLE_Q)
		{
			char *str = head->value;
			size_t len = ft_strlen(str) - 2;
			char *str_sgl = (char *)ft_malloc(len + 1, ALLOC);
			if (str_sgl)
			{

				int i = 0;
				int j = 1;
				while (str[j] && str[j] != '\'')
					str_sgl[i++] = str[j++];
				str_sgl[i] = '\0';
				head->value = str_sgl;
			}
		}
		head = head->next;
	}
}
void remove_double_q(token_node *head)
{
	while (head)
	{
		if (head->type == DOUBLE_Q)
		{
			char *str = head->value;
			size_t len = ft_strlen(str) - 2;
			char *str_sgl = (char *)ft_malloc(len + 1, ALLOC);
			if (str_sgl)
			{

				int i = 0;
				int j = 1;
				while (str[j] && str[j] != '\"')
					str_sgl[i++] = str[j++];
				str_sgl[i] = '\0';
				head->value = str_sgl;
			}
		}
		head = head->next;
	}
}

int is_string_type(int type)
{
	return (type == STRING || type == SINGLE_Q || type == DOUBLE_Q || type == VAR || type == DOUBLE_DLR || type == EXIT_STATUS);
}
char *expand_heredoc(char *cmd, t_expand *env)
{
	int i = 0;
	char *buffer = NULL;
	while (cmd[i])
	{
		char *str_var = get_until_var(cmd + i);
		char *str_exp = ft_str_exp(str_var, env);
		if (!buffer)
			buffer = ft_strdup("");
		buffer = ft_strjoin(buffer, str_exp);
		i += ft_strlen(str_var);
	}
	return (buffer);
}
int write_to_file(char *buffer)
{
	int i;
	char *file_tmp = ft_strdup(".heredoc");
	i = 0;
	while (access(file_tmp, F_OK) != -1)
		file_tmp = ft_strjoin(".heredoc", ft_itoa(i++));
	int fd = open(file_tmp, O_CREAT | O_RDWR | O_TRUNC, 0777);
	int fd_read = open(file_tmp, O_RDWR | O_TRUNC, 0777);
	// ft_close_fds(fd_read, OPEN);
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
int ft_readline(int flag, char *dlmtr, t_expand *env)
{
	char *buffer;
	char *cmd;

	buffer = NULL;
	signal(SIGINT, ft_sig_handler_her_doc);
	while (1)
	{
		cmd = readline("> ");
		char *free_cmd = cmd;
		if (!ttyname(0))
		{
			free(free_cmd);
			open(ttyname(2), O_RDWR);
			return (-2);
		}
		if (!cmd)
			return (write_to_file(buffer));
		if (!ft_strcmp(cmd, dlmtr))
		{
			free(free_cmd);
			break;
		}
		if (flag != 1337)
			cmd = expand_heredoc(cmd, env);
		buffer = append_cmd_to_buffer(cmd, buffer);
		free(free_cmd);
	}
	return (write_to_file(buffer));
}
int readline_hdc(char *dlmtr, t_expand *env, int flag)
{
	char *buffer;
	buffer = NULL;
	return (ft_readline(flag, dlmtr, env));
}
void ft_heredoc(token_node *head, t_expand *env)
{
	char *buffer = NULL;
	int flag = 0;
	while (head)
	{
		if (head->type == HEREDOC)
		{
			token_node *tmp = head->next;
			if (tmp && tmp->type == SPC)
				tmp = tmp->next;
			while (tmp && is_string_type(tmp->type))
			{
				if (!flag && (tmp->type == SINGLE_Q || tmp->type == DOUBLE_Q))
					flag = 1337;
				if (!buffer)
					buffer = ft_strdup("");
				buffer = ft_strjoin(buffer, tmp->value);
				tmp = tmp->next;
			}
			if (!buffer)
				return;
			head->fd_hrd = readline_hdc(buffer, env, flag);
			buffer = NULL;
		}
		head = head->next;
	}
}

token_node *ft_concatenate(token_node *head)
{
	token_node *new = NULL;
	char *buffer = NULL;
	bool check = false;
	while (head != NULL)
	{
		if (is_string_type(head->type))
		{
			buffer = NULL;
			while (head != NULL && is_string_type(head->type))
			{
				if (head->flage)
					check = true;
				if (!buffer)
					buffer = ft_strdup("");
				buffer = ft_strjoin(buffer, head->value);
				head = head->next;
			}
			token_node *new_node = addnew_tkn_node(STRING, buffer, -2);
			if (check)
			{
				new_node->flage = true;
				check = false;
			}
			lstadd_back(&new, new_node);
		}
		else
		{
			lstadd_back(&new, addnew_tkn_node(head->type, head->value, head->fd_hrd));
			head = head->next;
		}
	}
	return new;
}
// void ft_free(token_node **head)
// {
// 	token_node *tmp;
// 	while ((*head))
// 	{
// 		tmp = (*head);
// 		(*head) = (*head)->next;
// 		free(tmp->value);
// 		// tmp->value = NULL;
// 		free(tmp);
// 		// tmp = NULL;
// 	}
// 	*head = NULL;
// }

bool is_redirection(int type)
{
	return (type == REDIRECT_APPEND || type == REDIRECT_IN || type == REDIRECT_OUT || type == HEREDOC);
}
void parse_redirection_token(token_node **head, token_node **new_node)
{
	int type;
	char *value;
	token_node *tmp = NULL;

	type = (*head)->type;
	int fd_hrd = (*head)->fd_hrd;
	tmp = (*head)->next;
	if (tmp && tmp->type == SPC)
	{
		(*head) = tmp;
		tmp = (*head)->next;
	}
	tmp = (*head)->next;
	if (tmp && tmp->type == SPC)
	{
		(*head) = tmp;
		tmp = (*head)->next;
	}
	(*head) = tmp;
	value = (*head)->value;
	token_node *new = addnew_tkn_node(type, value, fd_hrd);
	if ((*head)->flage)
		new->flage = true;
	lstadd_back(new_node, new);
	(*head) = (*head)->next;
}

token_node *ft_remove_redirect(token_node *head)
{
	token_node *new_node = NULL;

	while (head)
	{
		if (is_redirection(head->type))
			parse_redirection_token(&head, &new_node);
		else
		{
			lstadd_back(&new_node, addnew_tkn_node(head->type, head->value, -2));
			head = head->next;
		}
	}
	return (new_node);
}
void lst_addback_cmd(t_cmd **lst_cmd, t_cmd *new_cmd)
{
	t_cmd *tmp = *lst_cmd;

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
	t_cmd *new_cmd = (t_cmd *)ft_malloc(sizeof(t_cmd), ALLOC);
	if (!new_cmd)
		return (NULL);
	new_cmd->args = args;
	new_cmd->redir = head_cmd;
	new_cmd->infile = 0;
	new_cmd->outfile = 1;
	new_cmd->next = NULL;
	return (new_cmd);
}
t_cmd *ft_split_cmd(token_node *new_head)
{
	int count = 0;
	token_node *tmp = new_head;
	token_node *redir = NULL;

	while (tmp)
	{
		if (tmp->type == STRING)
			count++;
		tmp = tmp->next;
	}
	char **args = (char **)ft_malloc(sizeof(char *) * (count + 1), ALLOC);
	if (!args)
		return (NULL);
	int i = 0;

	while (new_head)
	{
		if (new_head->type == STRING)
			args[i++] = new_head->value; // args[i++] = ft_strdup(new_head->value);

		if (is_redirection(new_head->type))
		{
			token_node *new = addnew_tkn_node(new_head->type, new_head->value, new_head->fd_hrd);
			if (new_head->flage)
				new->flage = true;
			lstadd_back(&redir, new);
		}
		new_head = new_head->next;
	}
	args[i] = NULL;
	return (addnew_cmd(args, redir));
}
t_cmd *ft_passing(token_node *head)
{
	t_cmd *new_cmd = NULL;
	while (head)
	{
		token_node *new_head = NULL;
		while (head)
		{
			if (head->type == PIPE)
				break;
			token_node *new_node = addnew_tkn_node(head->type, head->value, head->fd_hrd);
			if (head->flage)
				new_node->flage = true;
			lstadd_back(&new_head, new_node);
			head = head->next;
		}
		lst_addback_cmd(&new_cmd, ft_split_cmd(new_head));
		if (head)
			head = head->next;
	}
	return (new_cmd);
}

void ll()
{
	system("leaks minishell");
}
int main(int ac, char const *av[], char *env[])
{
	// atexit(ll);
	(void)ac;
	(void)av;
	(void)env;
	const char *cmd = NULL;
	token_node *head = NULL;
	t_cmd *cmd_list = NULL;
	int exit_status;
	(void)env;
	(void)cmd_list;
	head = NULL;
	t_expand *env_expand = NULL;
	rl_catch_signals = 0;
	init_env(&env_expand, env);

	rl_catch_signals = 0;
	while (1 && isatty(STDIN_FILENO))
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, handler);
		// puts("======");
		head = NULL;
		cmd = readline("➜ minishell ");
		if (g_sig == 1)
			exit_status = g_sig;
		if (!cmd)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		add_history(cmd);
		head = tokenization(cmd, &head);
		int error = handle_errors_cmd(head, cmd);
		remove_single_q(head);
		remove_double_q(head);
		ft_heredoc(head, env_expand);
		if (error == -1)
		{
			exit_status = 258;
			free((void *)cmd);
			ft_malloc(FREE, FREE);
			continue;
		}
		head = expand_and_print_vars(head, env_expand, exit_status);
		head = ft_concatenate(head);
		head = ft_remove_redirect(head);
		cmd_list = ft_passing(head);
		ft_execution(cmd_list, &env_expand, &exit_status);

		// displayLinkedList(head);
		// (void)cmd_list;
		// while (cmd_list)
		// {
		// 	printf("args: ");
		// 	for (int i = 0; cmd_list->args[i]; i++)
		// 		printf("(%s) ", cmd_list->args[i]);
		// 	printf("\n");
		// 	printf("redir: ");
		// 	token_node *tmp = cmd_list->redir;
		// 	while (tmp)
		// 	{
		// 		printf("%s ", tmp->value);
		// 		printf("%d ", tmp->flage);
		// 		printf(" %s ", "|");

		// 		tmp = tmp->next;
		// 	}
		// 	cmd_list = cmd_list->next;
		// 	printf("\n");
		// }
		free((void *)cmd);
		ft_malloc(FREE, FREE);
		ft_close_fds(FREE, CLOSE);
		g_sig = 0;
	}

	return 0;
}
