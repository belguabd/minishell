/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/11 14:17:44 by belguabd         ###   ########.fr       */
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
void handle_errors_cmd(const char *buffer)
{
	size_t i = 0;
	size_t len = ft_strlen(buffer);

	while (i < len)
	{
		if (buffer[i] == '\"' || buffer[i] == '\'')
		{
			i++;
			quote_error_handling(buffer, &i, buffer[i - 1]);
		}
		i++;
	}

	// if (quote_error_handling(buffer) == -1)
	// 	return;
	i = 0;

	while (buffer[i])
	{
		if (buffer[i] == '>' && buffer[i + 1] == '<')
		{
			printf("Error: syntax error\n");
			return;
		}
		if (buffer[i] == '<' || buffer[i] == '>')
		{
			if (buffer[i + 1] == '<' || buffer[i + 1] == '>')
				i++;
			if ((buffer[i + 1] == '>' || buffer[i + 1] == '<' || buffer[i + 1] == '|') && buffer[i + 1] == '\0')
			{
				printf("Error: syntax error\n");
				return;
			}
		}
		i++;
	}

	i = 0;
	if (buffer[i] == '|')
	{
		ft_putendl_fd("Error: syntax error near unexpected token `|'", 2);
		return;
	}
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '|')
		{
			if (buffer[i + 1] == '\0')
			{
				ft_putendl_fd("Error: syntax error near unexpected token `newline`", 2);
				return;
			}
		}
		i++;
	}

	i = 0;

	while (buffer[i])
	{
		if (buffer[i] == '|')
		{
			if (buffer[i + 1] == '|')
			{
				ft_putendl_fd("Error: syntax error near unexpected token `|'", 2);
				return;
			}
		}
		i++;
	}
	i = 0;
	while (buffer[i]) //< |, > |, >> |, << | : error
	{
		if ((buffer[i] == '>' || buffer[i] == '<') &&
			(buffer[i + 1] == '|' || (buffer[i] == '>' && buffer[i + 1] == '>' && buffer[i + 2] == '|') ||
			 (buffer[i] == '<' && buffer[i + 1] == '<' && buffer[i + 2] == '|')))
		{
			ft_putendl_fd("Error: syntax error near unexpected token `|'", 2);
			return;
		}
		i++;
	}
	i = 0;
	while (buffer[i]) // echo < , echo >, echo >> , echo << : error
	{
		if ((buffer[i] == '>' || buffer[i] == '<') &&
			(buffer[i + 1] == '\0' || (buffer[i] == '>' && buffer[i + 1] == '>' && buffer[i + 2] == '\0') ||
			 (buffer[i] == '<' && buffer[i + 1] == '<' && buffer[i + 2] == '\0')))
		{
			ft_putendl_fd("Error: syntax error near unexpected token `newline'", 2);
			return;
		}
		i++;
	}
}

int main()
{
	const char *cmd = NULL;
	token_node *head;
	head = NULL;
	while (1)
	{
		cmd = readline(COLOR_GREEN "minishell$ " COLOR_RESET);
		char *buffer = merge_substrings(cmd);
		printf("%s\n", buffer);
		handle_errors_cmd(buffer);
		head = tokenization(cmd, &head);

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
