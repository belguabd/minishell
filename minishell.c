/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:54:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/03 21:38:25 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn_node *addnew_tkn_node(t_token token, char *value)
{
	t_tkn_node *new;
	new = (t_tkn_node *)malloc(sizeof(t_tkn_node));
	if (!new)
		return (NULL);
	new->type = token;
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}
int check_cmd(char *cmd)
{
	int i = 0;
	char *ls = "ls";
	while (cmd[i] && ls[i] && ls[i] == cmd[i])
		i++;
	return (cmd[i] - ls[i]);
}
void lstadd_back(t_tkn_node **lst, t_tkn_node *new)
{
	if (!*lst)
	{
		*lst = new;
		return;
	}
	while ((*lst)->next)
		*lst = (*lst)->next;
	*lst = new;
}
void tokenization(char *cmd, t_tkn_node **head)
{
	
}
int main()
{
	char *input;
	t_tkn_node *head;
	head = NULL;
	while (1)
	{
		input = readline(COLOR_GREEN "minishell$ " COLOR_RESET);
		tokenization(input, &head);
	}
	return 0;
}
