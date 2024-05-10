/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 05:11:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:44:42 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	to_find;

	i = 0;
	to_find = 0;
	while (*str)
	{
		if (*str != c && to_find == 0)
		{
			to_find = 1;
			i++;
		}
		else if (*str == c)
			to_find = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int end, int *flag)
{
	char	*word;
	int		i;

	word = (char *)ft_malloc(((end - start) + 1) * sizeof(char), ALLOC);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	*flag = 1;
	return (word);
}

char	**ft_split(char const *str, char c)
{
	t_vars	var;

	if (!str)
		return (NULL);
	var.res = (char **)ft_malloc_env(
			(count_words(str, c) + 1) * sizeof(char *), ALLOC);
	if (!var.res)
		return (NULL);
	var.i = -1;
	var.j = 0;
	var.flag = 1;
	while (++var.i <= ft_strlen(str))
	{
		if (str[var.i] != c && var.flag > 0)
		{
			var.start = var.i;
			var.flag = 0;
		}
		else if ((str[var.i] == c || !str[var.i]) && var.flag == 0)
			var.res[var.j++] = word_dup(str, var.start, var.i, &var.flag);
	}
	return (var.res[var.j] = 0, var.res);
}
