/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/12 15:28:53 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
token_node *ft_lstlast(token_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
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
	return (c == '\"' || c == '\'' || c == '$' || c == '|' || c == '>' || c == '<' || c == ' ' || c == '\t');
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
		else if (cmd[i] == '$')
		{
			t_token tokenType;
			size_t j = i;
			start = j;
			while (cmd[j] && cmd[j] == '$')
				j++;
			if ((j - i) % 2 == 0)
				tokenType = UNKNOWN;
			else
				tokenType = VAR;
			while (cmd[j] && !is_string(cmd[j]))
				j++;
			end = --j;
			str = ft_substr(cmd, start, end - start + 1);
			lstadd_back(head, addnew_tkn_node(tokenType, str));
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
			end = --j; //--i overflow i += ft_strlen(ft_lstlast(*head)->value);

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
char *merge_substrings(const char *cmd)
{
	int i = 0;
	int start = 0;
	int end = 0;
	char *buffer;
	buffer = NULL;
	char *str;

	while (cmd[i])
	{
		while (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
			i++;
		start = i;
		while (cmd[i] && cmd[i] != ' ' && !(cmd[i] >= 9 && cmd[i] <= 13))
			i++;
		end = i;
		str = ft_substr(cmd, start, end - start);
		if (!buffer)
			buffer = ft_strdup("");
		char *tmp = buffer;
		buffer = ft_strjoin(buffer, str);
		free(tmp);
		free(str);
	}
	return (buffer);
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
	while (tmp) // redirection
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
void init_env(t_expand **head, char *env[])
{
	int i = 0;
	while (env[i] != NULL)
	{
		char **arr = ft_split(env[i], '=');
		int j = 0;
		if (arr[0] && arr[1])
		{
			t_expand *new_node = addnew_expand_node(arr[0], arr[1]);
			lstadd_back_expand(head, new_node);
			while (arr[j] != NULL)
				free(arr[j++]);
		}
		free(arr);
		i++;
	}
}
int main(int ac, char const *av[], char *env[])
{
	(void)ac;
	(void)av;
	const char *cmd = NULL;
	token_node *head;
	t_expand *env_expand = NULL;
	head = NULL;
	while (1)
	{
		cmd = readline(COLOR_GREEN "minishell$ " COLOR_RESET);
		add_history(cmd);
		head = tokenization(cmd, &head);
		init_env(&env_expand, env);
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
