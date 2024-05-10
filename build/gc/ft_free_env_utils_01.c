/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env_utils_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:41:23 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:45:22 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_env(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	string = ft_malloc_env((ft_strlen(s1) + ft_strlen(s2)) + 1, ALLOC);
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		string[i] = s2[j];
		i++;
		j++;
	}
	string[i] = '\0';
	return ((char *)string);
}

char	*ft_strdup_env(const char *s1)
{
	char	*string;
	int		len;
	int		i;

	len = ft_strlen(s1);
	string = (char *)ft_malloc_env((len + 1) * sizeof(char), ALLOC);
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	*ft_substr_env(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len_str;

	if (!s)
		return (NULL);
	len_str = ft_strlen(s);
	if (start >= len_str)
		return (ft_strdup_env(""));
	if (len_str < len + start)
		len = len_str - start;
	res = (char *)ft_malloc_env(len + 1, ALLOC);
	if (!res)
		return (NULL);
	i = start;
	j = 0;
	while (i < len_str && j < len)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}

t_expand	*addnew_expand_node_env(char *key, char *value)
{
	t_expand	*new_node;

	new_node = (t_expand *)ft_malloc_env(sizeof(t_expand), ALLOC);
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup_env(key);
	new_node->value = ft_strdup_env(value);
	new_node->next = NULL;
	return (new_node);
}

void	lstadd_back_expand_env(t_expand **lst, t_expand *new_node)
{
	t_expand	*last;

	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new_node;
}
