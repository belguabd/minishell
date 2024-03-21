/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/20 23:32:47 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
bool is_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}
token_node *ft_lstlast(token_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
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
bool is_string(char c)
{
	return (c == '\"' || c == '\'' || c == '|' || c == '>' || c == '$' || c == '<' || c == ' ' || c == '\t');
}
token_node *addnew_tkn_node(t_token token, char *value)
{
	token_node *new;
	new = (token_node *)malloc(sizeof(token_node));
	if (!new)
		return (NULL);
	new->type = token;
	new->value = value;
	new->next = NULL;
	return (new);
}
void lstadd_back(token_node **lst, token_node *new)
{
	if (!*lst)
	{
		*lst = new;
		return;
	}
	token_node *cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

// char *get_var(const char *cmd, int j)
// {
// 	int i = j;
// 	if (cmd[i] >= '0' && cmd[i] <= '9')
// 		return (ft_substr(cmd + i, i - 1, 1));
// 	while (cmd[i] && ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == '_'))
// 		i++;
// 	return (ft_substr(cmd, j, i - j));
// }
token_node *tokenization(const char *cmd, token_node **head)
{
	size_t i = 0;
	size_t start = 0;
	size_t end = 0;
	char *str;
	size_t len = ft_strlen(cmd);
	while (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
		i++;
	while (i < len) // use len of handle overflow
	{
		if (cmd[i] == '|')
			lstadd_back(head, addnew_tkn_node(PIPE, "|"));
		else if (cmd[i] == '$' && cmd[i + 1] == '?')
			lstadd_back(head, addnew_tkn_node(EXIT_STATUS, "$?"));
		else if (cmd[i] == '$')
		{
			int count = i;
			int start = i;
			while (cmd[count] && cmd[count] == '$')
				count++;
			printf("%d\n", count);
			printf("%d\n", start);
			count = count - start;
			printf("%d\n", count);
			if (count % 2 != 0)
			{
				size_t j = i;
				start = j;
				while (cmd[j] && cmd[j] == '$')
					j++;
				end = j;
				if (cmd[j] >= '0' && cmd[j] <= '9')
				{
					char *str = ft_substr(cmd, start, (end + 1) - start);
					lstadd_back(head, addnew_tkn_node(VAR, str));
				}
				else
				{
					if (is_var(cmd[j]))
					{
						while (ft_isalnum(cmd[j]) || cmd[j] == '_')
							j++;
						end = j;

						char *str = ft_substr(cmd, start, (end)-start);
						lstadd_back(head, addnew_tkn_node(VAR, str));
					}
					else
						lstadd_back(head, addnew_tkn_node(STRING, "$"));
				}
			}
			else
			{
				start = i;
				int j = i;
				while (cmd[j] && cmd[j] == '$')
					j++;
				end = j;
				if (cmd[j] >= '0' && cmd[j] <= '9')
				{
					char *str = ft_substr(cmd, start, (end + 1) - start);
					lstadd_back(head, addnew_tkn_node(STRING, str));
				}
				else
				{
					while (cmd[j] && ((cmd[j] >= 'a' && cmd[j] <= 'z') || (cmd[j] >= 'A' && cmd[j] <= 'Z') || (cmd[j] >= '0' && cmd[j] <= '9') || cmd[j] == '_'))
						j++;
					end = j;
					char *str = ft_substr(cmd, start, (end)-start);
					lstadd_back(head, addnew_tkn_node(STRING, str));
				}
			}
		}
		else if (cmd[i] == '>' && cmd[i + 1] == '>')
			lstadd_back(head, addnew_tkn_node(REDIRECT_APPEND, ">>"));
		else if (cmd[i] == '<' && cmd[i + 1] == '<')
			lstadd_back(head, addnew_tkn_node(HEREDOC, "<<"));
		else if (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
		{
			lstadd_back(head, addnew_tkn_node(SPACE, " "));
			while (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
				i++;
			i--;
		}
		else if (cmd[i] == '\'')
		{
			int j = i;
			start = j;
			j++;
			while (cmd[j])
			{
				if (cmd[j] == '\'')
					break;
				j++;
			}
			end = j;
			str = ft_substr(cmd, start, (end + 1) - start);
			lstadd_back(head, addnew_tkn_node(SINGLE_Q, str));
		}
		else if (cmd[i] == '\"')
		{
			int j = i;
			start = j;
			j++;
			while (cmd[j])
			{
				if (cmd[j] == '\"')
					break;
				j++;
			}

			end = j;
			str = ft_substr(cmd, start, (end + 1) - start);
			lstadd_back(head, addnew_tkn_node(DOUBLE_Q, str));
		}
		else if (cmd[i] == '>')
			lstadd_back(head, addnew_tkn_node(REDIRECT_OUT, ">"));
		else if (cmd[i] == '<')
			lstadd_back(head, addnew_tkn_node(REDIRECT_IN, "<"));
		else
		{
			int j = i;
			start = j;
			while (cmd[j] && !is_string(cmd[j]))
				j++;
			end = --j;
			str = ft_substr(cmd, start, (end + 1) - start);
			lstadd_back(head, addnew_tkn_node(STRING, str));
		}
		i += ft_strlen(ft_lstlast(*head)->value);
	}
	return (*head);
}
int ft_strcmp(const char *str1, const char *str2)
{
	int i = 0;

	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

void quote_error_handling(const char *buffer, size_t *i, char c)
{
	while (buffer[(*i)] && buffer[(*i)] != c)
		(*i)++;
	if (buffer[(*i)] && buffer[(*i)] == c)
		return;
	else
	{
		ft_putendl_fd("close quote", 2);
		return;
	}
}
void handle_errors_cmd(token_node *head, const char *cmd)
{
	size_t i = 0;
	size_t len = ft_strlen(cmd);
	while (i < len)
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i++;
			quote_error_handling(cmd, &i, cmd[i - 1]);
		}
		i++;
	}
	token_node *tmp = head;
	while (tmp)
	{
		if (tmp->type >= REDIRECT_APPEND && tmp->type <= HEREDOC)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == SPACE)
				tmp = tmp->next;
			if (tmp && tmp->type != STRING && tmp->type != DOUBLE_Q && tmp->type != SINGLE_Q && tmp->type != VAR)
			{
				printf("ERROR1\n");
				return;
			}
			if (!tmp)
			{
				printf("ERROR2\n");
				return;
			}
		}
		tmp = tmp->next;
	}
	tmp = head; // check pipe in line start
	if (tmp->type == SPACE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
	{
		printf("ERROR3\n");
		return;
	}

	tmp = head;
	// int size = ft_lstsize(tmp);
	while (tmp) //||
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp && tmp->type == SPACE)
				tmp = tmp->next;
			if (tmp && tmp->type == PIPE)
			{
				printf("ERROR4\n");
				return;
			}
			if (!tmp)
			{
				printf("ERROR4\n");
				return;
			}
		}
		tmp = tmp->next;
	}
}
// void skip_whitespace(token_node **lst)
// {
// 	token_node *tmp = *lst;
// 	while (tmp)
// 	{

// 		if (tmp->type == SPACE)
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
char *remove_double_q(char *str)
{
	int len = ft_strlen(str) - 2; // 2 for double quotes
	char *new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	int j = 1;
	int i = 0;
	while (str[j] && str[j] != '\"')
		new[i++] = str[j++];
	new[i] = '\0';
	return (new);
}
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
	int i = 0;
	char *get_var = NULL;
	char *str_exp = NULL;
	while (str_var[i])
	{
		if (str_var[i] == '$')
		{
			size_t count = i;
			while (str_var[i] && str_var[i] == '$')
				i++;
			count = i - count;
				// printf("%s\n",str_var);
			if (count % 2 != 0)
			{
				puts("OK");
				// printf("%s\n", str_var +i);
				// printf("%c\n", str_var[i]);
				// exit(0);
				// if (is_var())
				// {
				// }
				get_var = ft_get_var(str_var + i);
				str_exp = get_str_env(env, get_var);
				break;
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
		// 	if (tmp && tmp->type == SPACE)
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
			str = remove_double_q(str); // overflow in test (ls "-la )
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
int main(int ac, char const *av[], char *env[])
{
	(void)ac;
	(void)av;
	const char *cmd = NULL;
	token_node *head;
	t_expand *env_expand = NULL;
	(void)env_expand;
	(void)env;
	head = NULL;
	while (1)
	{
		cmd = readline(COLOR_GREEN "➜  minishell " COLOR_RESET);
		add_history(cmd);
		head = tokenization(cmd, &head);
		init_env(&env_expand, env);
		expand_and_print_vars(head, env_expand);
		remove_single_q(head);
		// display_expand_list(env_expand);
		handle_errors_cmd(head, cmd);
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