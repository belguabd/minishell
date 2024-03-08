/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/08 15:02:46 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
t_tkn_node *ft_lstlast(t_tkn_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}
void displayLinkedList(t_tkn_node *head)
{
	printf("\n+--------+---------------+\n");
	printf("|  Index |     Value     |\n");
	printf("+--------+---------------+\n");

	int index = 0;
	while (head != NULL)
	{
		printf("|%7d | %-14s|\n", index++, head->value);
		head = head->next;
	}
	printf("+--------+---------------+\n");
}
bool is_string(char c)
{
	return (c == '\"' || c == '\'' || c == '$' || c == '>' || c == '<' || c == ' ' || c == '\t');
}
t_tkn_node *addnew_tkn_node(t_token token, char *value)
{
	t_tkn_node *new;
	new = (t_tkn_node *)malloc(sizeof(t_tkn_node));
	if (!new)
		return (NULL);
	new->type = token;
	new->value = value;
	new->next = NULL;
	return (new);
}
void lstadd_back(t_tkn_node **lst, t_tkn_node *new)
{
	if (!*lst)
	{
		*lst = new;
		return;
	}
	t_tkn_node *cur = *lst;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

t_tkn_node *tokenization(char *cmd, t_tkn_node **head)
{
	size_t i = 0;
	size_t start = 0;
	size_t end = 0;
	char *str;
	while (cmd[i])
	{
		if (cmd[i] == '|')
			lstadd_back(head, addnew_tkn_node(PIPE, "|"));
		else if (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
		{
			lstadd_back(head, addnew_tkn_node(SPACE, " "));
			while (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13))
				i++;
			i--;
		}
		else if (cmd[i] == '>')
			lstadd_back(head, addnew_tkn_node(REDIRECT_OUT, ">"));
		
		i += ft_strlen(ft_lstlast(*head)->value);
	}
	displayLinkedList(*head);
	return (*head);
}

int main()
{
	char *input;
	t_tkn_node *head;
	head = NULL;
	while (1)
	{
		input = readline(COLOR_GREEN "minishell$ " COLOR_RESET);
		head = tokenization(input, &head);
		t_tkn_node *tmp;
		while (head)
		{
			tmp = head;
			head = head->next;
			free(tmp);
		}
	}

	return 0;
}
