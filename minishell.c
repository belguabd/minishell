/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/10 08:48:11 by belguabd         ###   ########.fr       */
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

token_node *tokenization(char *cmd, token_node **head)
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
			lstadd_back(head, addnew_tkn_node(REDIRECT_OUT, "<"));
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
int ft_strcmp(char *str1, char *str2)
{
	int i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}
void handle_errors(token_node *head)
{
	token_node *curr = head;
	if (!ft_strcmp(head->value, "|")) // starting with pipe generates error : | echo coucou
	{
		write(2, "Error: Unexpected pipe symbol '|'\n", 34);
		exit(EXIT_FAILURE);
	}
	while (curr)
	{
		if (ft_strcmp(curr->value, ">"))
		{
			while ()
			{
					
			}
			
		}
		curr = curr->next;
	}
}
int main()
{
	char *input = NULL;
	token_node *head;
	head = NULL;
	while (1)
	{
		input = readline(COLOR_GREEN "minishell$ " COLOR_RESET);
		head = tokenization(input, &head);
		handle_errors(head);
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
