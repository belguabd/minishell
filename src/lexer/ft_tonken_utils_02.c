/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tonken_utils_02.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:00:31 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:42:55 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_single_double(t_token_node **head, const char *cmd, int i)
{
	if (cmd[i] == '\'')
	{
		handle_single_quotes(i, cmd, head);
		return (0);
	}
	else if (cmd[i] == '\"')
	{
		handle_double_quotes(i, cmd, head);
		return (0);
	}
	return (-1);
}

int	ft_dollar(t_token_node **head, const char *cmd, int *i)
{
	if (cmd[(*i)] == '$' && cmd[(*i) + 1] == '?')
	{
		lstadd_back(head, addnew_tkn_node(EXIT_STATUS, "$?", -2));
		return (0);
	}
	else if (cmd[(*i)] == '$' && cmd[(*i) + 1] == '$')
	{
		lstadd_back(head, addnew_tkn_node(DOUBLE_DLR, "$$", -2));
		return (0);
	}
	else if ((cmd[(*i)] == '$' && cmd[(*i) + 1] == '\"')
		|| (cmd[(*i)] == '$' && cmd[(*i) + 1] == '\''))
	{
		lstadd_back(head, addnew_tkn_node(STRING, "", -2));
		(*i)++;
		return (0);
	}
	else if (cmd[(*i)] == '$')
	{
		ft_process_vars(cmd, head, (*i));
		return (0);
	}
	return (-1);
}

int	ft_spaces(t_token_node **head, const char *cmd, int *i)
{
	if (cmd[(*i)] && (cmd[(*i)] == ' ' || (cmd[(*i)] >= 9 && cmd[(*i)] <= 13)))
	{
		lstadd_back(head, addnew_tkn_node(SPC, " ", -2));
		while (cmd[(*i)] && (cmd[(*i)] == ' '
				|| (cmd[(*i)] >= 9 && cmd[(*i)] <= 13)))
			(*i)++;
		(*i)--;
		return (0);
	}
	return (-1);
}

void	handle_single_quotes(int start, const char *cmd, t_token_node **head)
{
	int		j;
	char	*str;

	j = start;
	j++;
	while (cmd[j])
	{
		if (cmd[j] == '\'')
			break ;
		j++;
	}
	str = ft_substr(cmd, start, (j + 1) - start);
	lstadd_back(head, addnew_tkn_node(SINGLE_Q, str, -2));
}

void	handle_double_quotes(int start, const char *cmd, t_token_node **head)
{
	int		j;
	char	*str;

	j = start;
	j++;
	while (cmd[j])
	{
		if (cmd[j] == '\"')
			break ;
		j++;
	}
	str = ft_substr(cmd, start, (j + 1) - start);
	lstadd_back(head, addnew_tkn_node(DOUBLE_Q, str, -2));
}
