/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tonken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 09:36:33 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:42:58 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_process_odd(const char *cmd, t_token_node **head, int start)
{
	char	*str;
	size_t	j;

	j = start;
	while (cmd[j] && cmd[j] == '$')
		j++;
	if (cmd[j] >= '0' && cmd[j] <= '9')
	{
		str = ft_substr(cmd, start, (j + 1) - start);
		lstadd_back(head, addnew_tkn_node(VAR, str, -2));
	}
	else
	{
		if (is_var(cmd[j]))
		{
			while (ft_isalnum(cmd[j]) || cmd[j] == '_')
				j++;
			str = ft_substr(cmd, start, j - start);
			lstadd_back(head, addnew_tkn_node(VAR, str, -2));
		}
		else
			lstadd_back(head, addnew_tkn_node(STRING, "$", -2));
	}
}

void	ft_process_vars(const char *cmd, t_token_node **head, int i)
{
	int		start;
	char	*str;

	start = i;
	str = NULL;
	i++;
	if (cmd[i] >= '0' && cmd[i] <= '9')
		str = ft_substr(cmd, start, (i + 1) - start);
	else
	{
		while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
			i++;
		str = ft_substr(cmd, start, i - start);
	}
	lstadd_back(head, addnew_tkn_node(VAR, str, -2));
}

void	handle_string(int start, const char *cmd, t_token_node **head)
{
	char	*str;
	int		j;

	j = start;
	while (cmd[j] && !is_string(cmd[j]))
		j++;
	str = ft_substr(cmd, start, j - start);
	lstadd_back(head, addnew_tkn_node(STRING, str, -2));
}

int	ft_redirection(t_token_node **head, const char *cmd, int i)
{
	if (cmd[i] == '>' && cmd[i + 1] == '>')
	{
		lstadd_back(head, addnew_tkn_node(REDIRECT_APPEND, ">>", -2));
		return (0);
	}
	else if (cmd[i] == '<' && cmd[i + 1] == '<')
	{
		lstadd_back(head, addnew_tkn_node(HEREDOC, "<<", -2));
		return (0);
	}
	else if (cmd[i] == '>')
	{
		lstadd_back(head, addnew_tkn_node(REDIRECT_OUT, ">", -2));
		return (0);
	}
	else if (cmd[i] == '<')
	{
		lstadd_back(head, addnew_tkn_node(REDIRECT_IN, "<", -2));
		return (0);
	}
	return (-1);
}

t_token_node	*tokenization(const char *cmd, t_token_node **head)
{
	int		i;
	size_t	len;

	len = ft_strlen(cmd);
	i = 0;
	while (cmd[i] && (cmd[i] == ' ' || (cmd[i] >= 9 && cmd[i] <= 13)))
		i++;
	while ((size_t)i < len)
	{
		if (cmd[i] == '|')
			lstadd_back(head, addnew_tkn_node(PIPE, "|", -2));
		else if (!ft_dollar(head, cmd, &i))
			;
		else if (!ft_spaces(head, cmd, &i))
			;
		else if (!ft_single_double(head, cmd, i))
			;
		else if (!ft_redirection(head, cmd, i))
			;
		else
			handle_string(i, cmd, head);
		i += ft_strlen(ft_lstlast(*head)->value);
	}
	return (*head);
}
