/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_last_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 01:21:09 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:44:38 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strncpy(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str2[i] && i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
	return (str1);
}

int	count_words(char *cmd)
{
	int	wc;
	int	i;

	wc = 0;
	i = 0;
	while (cmd[i])
	{
		while (cmd[i] && is_space(cmd[i]))
			i++;
		if (cmd[i])
			wc++;
		while (cmd[i] && not_space(cmd[i]))
			i++;
	}
	return (wc);
}

char	**ft_tab(char **tab, char *cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (cmd[i])
	{
		while (cmd[i] && is_space(cmd[i]))
			i++;
		j = i;
		while (cmd[i] && not_space(cmd[i]))
			i++;
		if (i > j)
		{
			tab[k] = (char *)ft_malloc(sizeof(char) * ((i - j) + 1), ALLOC);
			ft_strncpy(tab[k++], &cmd[j], i - j);
		}
	}
	tab[k] = NULL;
	return (tab);
}

char	**ft_split_last_cmd(char *cmd)
{
	char	**tab;
	int		wc;

	if (!cmd)
		return (NULL);
	wc = count_words(cmd);
	tab = (char **)ft_malloc(sizeof(char *) * (wc + 1), ALLOC);
	return (ft_tab(tab, cmd));
}
