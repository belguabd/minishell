/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/27 01:53:43 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void displayLinkedList(token_node *head)
{
	printf("\n+--------+---------------+\n");
	printf("|  Index |     Value     |\n");
	printf("+--------+---------------+\n");

	// int index = 0;
	while (head != NULL)
	{
		printf("|%7d | %-14s|\n", head->type, head->value);
		head = head->next;
	}
	printf("+--------+---------------+\n");
}
int ft_strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

t_expand *addnew_expand_node(char *key, char *value)
{
	t_expand *new_node = (t_expand *)malloc(sizeof(t_expand));
	if (!new_node)
		return NULL;

	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return new_node;
}

void lstadd_back_expand(t_expand **lst, t_expand *new_node)
{
	if (!*lst)
	{
		*lst = new_node;
		return;
	}
	t_expand *last = *lst;
	while (last->next)
		last = last->next;

	last->next = new_node;
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

void init_env(t_expand **head, char *env[])
{
	int i = 0;
	while (env[i])
	{
		int j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		char *key = ft_substr(env[i], 0, j);
		char *value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j - 1);
		lstadd_back_expand(head, addnew_expand_node(key, value));
		i++;
	}
}
bool check_exist_env(char *str, t_expand *env)
{
	(void)str;
	while (env)
	{
		t_expand *tmp = env;
		env = env->next;
		free(tmp);
	}
	return (false);
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

	while (env)
	{
		if (!ft_strcmp(env->key, str_var))
			return (env->value);
		env = env->next;
	}
	return (ft_strdup(""));
}

void remove_single_q(token_node *head)
{
	while (head)
	{
		if (head->type == SINGLE_Q)
		{
			char *str = head->value;
			size_t len = ft_strlen(str) - 2;
			char *str_sgl = (char *)malloc(len + 1);
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
			char *str_sgl = (char *)malloc(len + 1);
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
	return (type == STRING || type == SINGLE_Q || type == DOUBLE_Q || type == VAR);
}
char *expand_heardoc(char *cmd, t_expand *env)
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
void readline_hdc(char *dlmtr, t_expand *env, int flag)
{
	static int i;
	(void)dlmtr;
	char *buffer = NULL;
	// char *file_tmp = ft_strdup("/tmp/file_tmp_");
	char *file_tmp = ft_strdup("file_tmp_");
	file_tmp = ft_strjoin(file_tmp, ft_itoa(i++));
	while (1)
	{
		char *cmd = readline("> ");
		if (!ft_strcmp(cmd, dlmtr))
			break;
		if (flag != 1337)
			cmd = expand_heardoc(cmd, env);
		if (!buffer)
			buffer = ft_strdup("");
		if (!cmd)
			cmd = ft_strdup("");
		buffer = ft_strjoin(buffer, cmd);
		buffer = ft_strjoin(buffer, "\n");
	}
	int fd = open(file_tmp, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
		write(2, "Error\n", 6);
	write(fd, buffer, ft_strlen(buffer));
}
void ft_headoc(token_node *head, t_expand *env)
{
	char *buffer = NULL;
	int flag = 0;
	while (head)
	{
		if (head->type == HEREDOC)
		{
			token_node *tmp = head->next;
			if (tmp && tmp->type == SPACE)
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
			readline_hdc(buffer, env, flag);
			buffer = NULL;
		}
		head = head->next;
	}
}

token_node *ft_concatenate(token_node *head)
{
	token_node *new = NULL;
	char *buffer = NULL;

	while (head != NULL)
	{
		if (is_string_type(head->type))
		{
			buffer = NULL;
			while (head != NULL && is_string_type(head->type))
			{
				if (!buffer)
					buffer = ft_strdup("");
				buffer = ft_strjoin(buffer, head->value);
				head = head->next;
			}
			lstadd_back(&new, addnew_tkn_node(STRING, buffer));
		}
		else
		{
			lstadd_back(&new, addnew_tkn_node(head->type, head->value));
			head = head->next;
		}
	}
	return new;
}
void ft_free(token_node **head)
{
	token_node *tmp;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

bool is_redirection(int type)
{
	return (type == REDIRECT_APPEND || type == REDIRECT_IN || type == REDIRECT_OUT || type == HEREDOC);
}
token_node *ft_remove_redirect(token_node *head)
{
	token_node *new_node = NULL;
	while (head)
	{
		if (is_redirection(head->type))
		{
			int type = head->type;
			token_node *tmp = head->next;
			if (tmp && tmp->type == SPACE)
				head = head->next;
			head = head->next; // skip the redirection token
			lstadd_back(&new_node, addnew_tkn_node(type, head->value));
			head = head->next; // Skip the value token
		}
		else
		{
			lstadd_back(&new_node, addnew_tkn_node(head->type, head->value));
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
	t_cmd *new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = args;
	new_cmd->redir = head_cmd;
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
	char **args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	int i = 0;

	while (new_head)
	{
		// puts("tbrgfdvfrgth5grfdvgrt");
		if (new_head->type == STRING)
			args[i++] = ft_strdup(new_head->value);
		if (is_redirection(new_head->type))
			lstadd_back(&redir, addnew_tkn_node(new_head->type, new_head->value));
		// printf("args: [%s]\n", args[i]);
		new_head = new_head->next;
	}
	args[i] = NULL;
	i = 0;
	// while (args[i])
	// {
	// 	printf("%s\n", args[i]);
	// 	i++;
	// }
	// exit(0);

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
			lstadd_back(&new_head, addnew_tkn_node(head->type, head->value));
			head = head->next;
		}
		lst_addback_cmd(&new_cmd, ft_split_cmd(new_head));
		if (head)
			head = head->next;
	}
	return (new_cmd);
}
void ft_free_all(t_free *head)
{
	t_free *current = head;
	while (current)
	{
		t_free *next = current->next;
		free(current->add);
		free(current);
		current = next;
	}
	head = NULL; 
}

t_free *addnew_free(void *add)
{
	t_free *new = malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	new->add = add;
	new->next = NULL;
	return (new);
}
void addback_free(t_free **head, t_free *new)
{
	t_free *tmp = *head;
	if (!tmp)
	{
		*head = new;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
void *ft_malloc(size_t size, int status)
{
	static t_free *head = NULL;
	if (status == ALLOC)
	{
		void *rt = malloc(size);
		if (!rt)
			return (NULL);
		addback_free(&head, addnew_free(rt));
		return (rt);
	}
	else
		ft_free_all(head);
	return (NULL);
}
int main(int ac, char const *av[], char *env[])
{
	(void)ac;
	(void)av;
	const char *cmd = NULL;
	token_node *head = NULL;
	t_expand *env_expand = NULL;
	(void)env_expand;
	t_cmd *cmd_list = NULL;

	(void)env;
	(void)cmd_list;
	head = NULL;
	init_env(&env_expand, env);
	while (1)
	{
		cmd = readline(COLOR_GREEN "➜  minishell " COLOR_RESET);
		// if (!cmd)
		// {
		// 	exit(exit_status_of_your_program)
		// }
		add_history(cmd);
		head = tokenization(cmd, &head);
		int error = handle_errors_cmd(head, cmd);
		if (error == -1)
		{
			ft_free(&head);
			continue;
		}
		expand_and_print_vars(head, env_expand);
		remove_single_q(head);
		remove_double_q(head);
		// ft_headoc(head, env_expand);
		head = ft_concatenate(head);

		// exit(0);
		// display_expand_list(env_expand);
		head = ft_remove_redirect(head);
		cmd_list = ft_passing(head);
		while (cmd_list)
		{
			printf("args: ");
			for (int i = 0; cmd_list->args[i]; i++)
				printf("%s ", cmd_list->args[i]);
			printf("\n");
			printf("redir: ");
			token_node *tmp = cmd_list->redir;
			while (tmp)
			{
				printf("%s ", tmp->value);
				tmp = tmp->next;
			}
			cmd_list = cmd_list->next;
			printf("\n");
		}

		displayLinkedList(head);
		token_node *tmp;
		while (head)
		{
			tmp = head;
			head = head->next;
			free(tmp);
		}
	}
	return 0;
}