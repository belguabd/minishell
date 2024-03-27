/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 05:11:22 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/27 20:40:29 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_free(char **res, char *str, int index)
{
	int	i;

	i = 0;
	if (!str)
	{
		while (i < index)
		{
			free(res[i]);
			i++;
		}
		free(res);
		return (0);
	}
	return (1);
}

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

	word = (char *)ft_malloc(((end - start) + 1) * sizeof(char),ALLOC);
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
	var.res = (char **)ft_malloc((count_words(str, c) + 1) * sizeof(char *) ,ALLOC);
	if (!var.res)
		return (NULL);
	var.i = -1;
	var.j = 0;
	var.flage = 1;
	while (++var.i <= ft_strlen(str))
	{
		if (str[var.i] != c && var.flage > 0)
		{
			var.start = var.i;
			var.flage = 0;
		}
		else if ((str[var.i] == c || !str[var.i]) && var.flage == 0)
		{
			var.res[var.j++] = word_dup(str, var.start, var.i, &var.flage);
			if (!ft_free(var.res, var.res[var.j - 1], var.j - 1))
				return (NULL);
		}
	}
	return (var.res[var.j] = 0, var.res);
}
