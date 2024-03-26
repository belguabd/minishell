/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/26 05:29:44 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define REDIRECT_APPEND 0 // >>
#define REDIRECT_OUT 1	  // >
#define REDIRECT_IN 2	  // <
#define HEREDOC 3		  // <<
#define SPACE_ 4
#define STRING 5   //"belguabd"
#define PIPE 6	   //"|"
#define DOUBLE_Q 7 //""
#define SINGLE_Q 8 //''
#define VAR 9	   // variable
#define EXIT_STATUS 10
#include <string.h>

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
// bool is_string(char c)
// {
// 	return (c == '\"' || c == '\'' || c == '|' || c == '>' || c == '$' || c == '<' || c == ' ' || c == '\t');
// }
// token_node *addnew_tkn_node(t_token token, char *value)
// {
// 	token_node *new;
// 	new = (token_node *)malloc(sizeof(token_node));
// 	if (!new)
// 		return (NULL);
// 	new->type = token;
// 	new->value = value;
// 	new->next = NULL;
// 	return (new);
// }
// token_node *addnew_tkn_node(int token, char *value)
// {
// 	token_node *new;
// 	new = (token_node *)malloc(sizeof(token_node));
// 	if (!new)
// 		return (NULL);
// 	new->type = token;
// 	new->value = value;
// 	new->next = NULL;
// 	return (new);
// }
// void lstadd_back(token_node **lst, token_node *new)
// {
// 	if (!*lst)
// 	{
// 		*lst = new;
// 		return;
// 	}
// 	token_node *cur = *lst;
// 	while (cur->next)
// 		cur = cur->next;
// 	cur->next = new;
// }

// char *get_var(const char *cmd, int j)
// {
// 	int i = j;
// 	if (cmd[i] >= '0' && cmd[i] <= '9')
// 		return (ft_substr(cmd + i, i - 1, 1));
// 	while (cmd[i] && ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == '_'))
// 		i++;
// 	return (ft_substr(cmd, j, i - j));
// }
// token_node *tokenization(const char *cmd, token_node **head)
// {
// 	size_t i = 0;
// 	size_t start = 0;
// 	size_t end = 0;
// 	char *str;
// 	size_t len = ft_strlen(cmd);
// 	while (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
// 		i++;
// 	while (i < len) // use len of handle overflow
// 	{
// 		if (cmd[i] == '|')
// 			lstadd_back(head, addnew_tkn_node(PIPE, "|"));
// 		else if (cmd[i] == '$' && cmd[i + 1] == '?')
// 			lstadd_back(head, addnew_tkn_node(EXIT_STATUS, "$?"));
// 		else if (cmd[i] == '$')
// 		{
// 			int count = i;
// 			int start = i;
// 			while (cmd[count] && cmd[count] == '$')
// 				count++;
// 			count = count - i;
// 			if (count % 2 != 0)
// 			{
// 				size_t j = i;
// 				start = j;
// 				while (cmd[j] && cmd[j] == '$')
// 					j++;
// 				end = j;
// 				if (cmd[j] >= '0' && cmd[j] <= '9')
// 				{
// 					char *str = ft_substr(cmd, start, (end + 1) - start);
// 					lstadd_back(head, addnew_tkn_node(VAR, str));
// 				}
// 				else
// 				{
// 					if (is_var(cmd[j]))
// 					{
// 						while (ft_isalnum(cmd[j]) || cmd[j] == '_')
// 							j++;
// 						end = j;

// 						char *str = ft_substr(cmd, start, (end)-start);
// 						lstadd_back(head, addnew_tkn_node(VAR, str));
// 					}
// 					else
// 						lstadd_back(head, addnew_tkn_node(STRING, "$"));
// 				}
// 			}
// 			else
// 			{
// 				start = i;
// 				int j = i;
// 				while (cmd[j] && cmd[j] == '$')
// 					j++;
// 				end = j;
// 				if (cmd[j] >= '0' && cmd[j] <= '9')
// 					str = ft_substr(cmd, start, (end + 1) - start);
// 				else
// 				{
// 					while (cmd[j] && (ft_isalnum(cmd[j]) || cmd[j] == '_'))
// 						j++;
// 					end = j;
// 					str = ft_substr(cmd, start, (end)-start);
// 				}
// 				lstadd_back(head, addnew_tkn_node(STRING, str));
// 			}
// 		}
// 		else if (cmd[i] == '>' && cmd[i + 1] == '>')
// 			lstadd_back(head, addnew_tkn_node(REDIRECT_APPEND, ">>"));
// 		else if (cmd[i] == '<' && cmd[i + 1] == '<')
// 			lstadd_back(head, addnew_tkn_node(HEREDOC, "<<"));
// 		else if (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
// 		{
// 			lstadd_back(head, addnew_tkn_node(SPACE_, " "));
// 			while (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
// 				i++;
// 			i--;
// 		}
// 		else if (cmd[i] == '\'')
// 		{
// 			int j = i;
// 			start = j;
// 			j++;
// 			while (cmd[j])
// 			{
// 				if (cmd[j] == '\'')
// 					break;
// 				j++;
// 			}
// 			end = j;
// 			str = ft_substr(cmd, start, (end + 1) - start);
// 			lstadd_back(head, addnew_tkn_node(SINGLE_Q, str));
// 		}
// 		else if (cmd[i] == '\"')
// 		{
// 			int j = i;
// 			start = j;
// 			j++;
// 			while (cmd[j])
// 			{
// 				if (cmd[j] == '\"')
// 					break;
// 				j++;
// 			}

// 			end = j;
// 			str = ft_substr(cmd, start, (end + 1) - start);
// 			lstadd_back(head, addnew_tkn_node(DOUBLE_Q, str));
// 		}
// 		else if (cmd[i] == '>')
// 			lstadd_back(head, addnew_tkn_node(REDIRECT_OUT, ">"));
// 		else if (cmd[i] == '<')
// 			lstadd_back(head, addnew_tkn_node(REDIRECT_IN, "<"));
// 		else
// 		{
// 			int j = i;
// 			start = j;
// 			while (cmd[j] && !is_string(cmd[j]))
// 				j++;
// 			end = --j;
// 			str = ft_substr(cmd, start, (end + 1) - start);
// 			lstadd_back(head, addnew_tkn_node(STRING, str));
// 		}
// 		i += ft_strlen(ft_lstlast(*head)->value);
// 	}
// 	return (*head);
// }
int ft_strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int quote_error_handling(const char *buffer, size_t *i, char c)
{
	while (buffer[(*i)] && buffer[(*i)] != c)
		(*i)++;
	if (buffer[(*i)] && buffer[(*i)] == c)
		return (0);
	else
	{
		ft_putendl_fd("close quote", 2);
		return (-1);
	}
	return (0);
}
int handle_errors_cmd(token_node *head, const char *cmd)
{
	size_t i = 0;
	size_t len = ft_strlen(cmd);
	while (i < len)
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i++;
			if (quote_error_handling(cmd, &i, cmd[i - 1]) == -1)
				return (-1);
		}
		i++;
	}
	token_node *tmp = head;
	while (tmp)
	{
		if (tmp->type >= REDIRECT_APPEND && tmp->type <= HEREDOC)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == SPACE_)
				tmp = tmp->next;
			if (tmp && tmp->type != STRING && tmp->type != DOUBLE_Q && tmp->type != SINGLE_Q && tmp->type != VAR)
			{
				ft_putendl_fd("syntax error near unexpected token", 2);
				return (-1);
			}
			if (!tmp)
			{
				ft_putendl_fd("syntax error near unexpected token", 2);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	tmp = head; // check pipe in line start
	if (tmp->type == SPACE_)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
	{
		ft_putendl_fd("syntax error near unexpected token", 2);
		return (-1);
	}

	tmp = head;
	// int size = ft_lstsize(tmp);
	while (tmp) //||
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == SPACE_)
				tmp = tmp->next;
			if (tmp && tmp->type == PIPE)
			{
				ft_putendl_fd("syntax error near unexpected token", 2);
				return (-1);
			}
			if (!tmp)
			{
				ft_putendl_fd("syntax error near unexpected token", 2);
				return (-1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
// void skip_whiteSPACE_(token_node **lst)
// {
// 	token_node *tmp = *lst;
// 	while (tmp)
// 	{

// 		if (tmp->type == SPACE_)
// 		{

// 		}
// 		tmp = tmp->next;
// 	}
// }
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
		// if (!ft_strncmp(str, env->key, ft_strlen(env->key)))
		// 	return (true);
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
char *ft_get_var(char *str_var)
{
	int i = 0;
	int start = 0;
	if (str_var[i] >= '0' && str_var[i] <= '9')
		return (ft_substr(str_var, i, 1));
	while (str_var[i] && (ft_isalnum(str_var[i]) || str_var[i] == '_'))
		i++;
	return (ft_substr(str_var, start, i));
}
// char *get_new_str(char *str, char *str_exp, char *str_var)
// {
// 	size_t len_totale = (ft_strlen(str) - (ft_strlen(str_var) + 1)) + ft_strlen(str_exp);
// 	char *new = (char *)malloc(len_totale + 1);
// 	if (!new)
// 		return (NULL);
// 	int i = 0;
// 	while (str[i] && str[i] != '$')
// 	{
// 		new[i] = str[i];
// 		i++;
// 	}
// }
// char *remove_double_q(char *str)
// {
// 	int len = ft_strlen(str) - 2; // 2 for double quotes
// 	char *new = (char *)malloc(len + 1);
// 	if (!new)
// 		return (NULL);
// 	int j = 1;
// 	int i = 0;
// 	while (str[j] && str[j] != '\"')
// 		new[i++] = str[j++];
// 	new[i] = '\0';
// 	return (new);
// }
char *get_until_var(char *str_var)
{
	int i = 0;
	int start = 0;
	while (str_var[i])
	{
		if (str_var[i] == '$')
		{
			while (str_var[i] && str_var[i] == '$')
				i++;
			while (str_var[i] && (ft_isalnum(str_var[i]) || str_var[i] == '_'))
				i++;
			break;
		}
		i++;
	}
	return (ft_substr(str_var, start, i));
}
char *get_string_exp(char *str, char *old_var, char *new_var)
{
	size_t len = (ft_strlen(str) - (ft_strlen(old_var))) + ft_strlen(new_var);

	if (ft_strlen(old_var))
		len++;
	// printf("%zu\n", len);
	// printf("%zu\n", ft_strlen(str));
	// printf("%zu\n", ft_strlen(old_var));
	// printf("%zu\n", ft_strlen(new_var));

	char *new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	int i = 0;
	while (str[i] && str[i] != '$')
	{
		new[i] = str[i];
		i++;
	}
	while (str[i] && str[i] == '$') //$$$HOME
	{
		if (str[i + 1] != '$')
			break;
		new[i] = str[i];
		i++;
	}
	int j = 0;
	if (new_var)
	{
		while (new_var[j])
		{
			new[i++] = new_var[j++];
		}
	}
	new[i] = '\0';
	return (new);
	// printf("%zu\n", len);
	// printf("%zu\n", ft_strlen(str));
	// printf("%zu\n", ft_strlen(old_var));
	// printf("%zu\n", ft_strlen(new_var));
	// printf("%s\n", str);
	// printf("%s\n", old_var);
	// printf("%s\n", new_var);

	// exit(0);
}
char *ft_str_exp(char *str_var, t_expand *env)
{
	size_t i = 0;
	char *get_var = NULL;
	char *str_exp = NULL;
	size_t len = ft_strlen(str_var);
	while (i < len)
	{
		if (str_var[i] == '$')
		{
			size_t count = i;
			while (str_var[i] && str_var[i] == '$')
				i++;
			count = i - count;
			if (count % 2 != 0)
			{
				get_var = ft_get_var(str_var + i);
				if (get_var[0])
					str_exp = get_str_env(env, get_var);
				else
				{
					str_exp = ft_strdup("$");
					break;
				}
			}
			else
			{
				get_var = ft_get_var(str_var + i);
				get_var = ft_strjoin("$", get_var);
				str_exp = get_var;
			}
		}
		i++;
	}

	return (get_string_exp(str_var, get_var, str_exp));
}

void expand_and_print_vars(token_node *head, t_expand *env)
{
	char *buffer = NULL;
	(void)buffer;
	(void)env;
	while (head)
	{
		// if (head->type == HEREDOC)
		// {
		// 	token_node *tmp = head->next;
		// 	if (tmp && tmp->type == SPACE_)
		// 		head = tmp;
		// 	if (head->next->type == VAR)
		// 		head = head->next;
		// }
		if (head->type == VAR)
		{
			int i = 0;
			char *str = head->value;
			int start = i;
			int end = 0;
			while (str[i] && str[i] == '$')
				i++;
			end = i - 1;
			if (str[i] >= '0' && str[i] <= '9')
				buffer = ft_strjoin(ft_substr(str, start, end), get_str_env(env, str + i));
			else
				buffer = ft_strjoin(ft_substr(str, start, end), get_str_env(env, str + i));
			free(head->value);
			head->value = buffer;
		}
		else if (head->type == DOUBLE_Q)
		{
			buffer = NULL;
			size_t i = 0;
			char *str = head->value;
			// str = remove_double_q(str); // overflow in test (ls "-la )
			while (str[i])
			{
				char *str_var = get_until_var(str + i);
				char *str_exp = ft_str_exp(str_var, env);
				if (!buffer)
					buffer = ft_strdup("");
				buffer = ft_strjoin(buffer, str_exp);
				i += ft_strlen(str_var);
			}
			head->value = buffer;
		}
		head = head->next;
	}
}
void remove_single_q(token_node *head)
{
	while (head) // overflow in test (ls '-la )
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
	while (head) // overflow in test (ls '-la )
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
			if (tmp && tmp->type == SPACE_)
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
			if (tmp && tmp->type == SPACE_)
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
t_cmd *ft_passing(token_node *head)
{
	// t_cmd *tmp = NULL;
	t_cmd *new_cmd = NULL;
	token_node *head_cmd = NULL;
	int count;
	while (head)
	{
		count = 0;
		token_node *tmp = head;
		while (tmp)
		{
			if (tmp->type == PIPE)
				break;
			if (tmp->type == STRING)
				count++;
			tmp = tmp->next;
		}
		char **args = (char **)malloc(sizeof(char *) * (count + 1));
		if (!args)
			return (NULL);
		int i = 0;
		while (head)
		{
			if (head->type == PIPE)
				break;
			if (head->type == STRING)
				args[i++] = ft_strdup(head->value);
			if (is_redirection(head->type))
				lstadd_back(&head_cmd, addnew_tkn_node(head->type, head->value));
			head = head->next;
		}
		args[i] = NULL;
		if (head && (head->type == PIPE))
		{
			lst_addback_cmd(&new_cmd, addnew_cmd(args, head_cmd));
			head_cmd = NULL;
		}
		if (!head)
		{
			lst_addback_cmd(&new_cmd, addnew_cmd(args, head_cmd));
			break;
		}
		if (head)
			head = head->next;
	}
	return (new_cmd);
}
// void f(t_cmd *head)
// {
// 	int input=2;
// 	int output = 3;
// 	while (head->redir)
// 	{
// 		if (head->redir->type == REDIRECT_OUT || head->redir->type == REDIRECT_APPEND) // >  FILE >> FILE2 > FILE2 < FILE4
//  		{
// 			fd = open();
// 			close()
// 			3
// 		}
// 		if(head->redir->type==REDIRECT_OUT){
			
// 		}
// 		head->redir = head->redir->next;
// 	}
// }
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
	while (1)
	{
		cmd = readline(COLOR_GREEN "➜  minishell " COLOR_RESET);
		add_history(cmd);
		head = tokenization(cmd, &head);
		int error = handle_errors_cmd(head, cmd);
		if (error == -1)
		{
			ft_free(&head);
			continue;
		}
		init_env(&env_expand, env);
		// expand_and_print_vars(head, env_expand);
		remove_single_q(head);
		remove_double_q(head);
		// ft_headoc(head, env_expand);
		// head = ft_concatenate(head);
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