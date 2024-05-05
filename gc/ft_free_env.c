/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 02:07:02 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/04 17:35:30 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char	*ft_strjoin_env(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	string = ft_malloc_env((ft_strlen(s1) + ft_strlen(s2)) + 1 ,ALLOC);
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
char *ft_strdup_env(const char *s1)
{
	int len;
	int i;
	char *string;

	len = ft_strlen(s1);
	string = (char *)ft_malloc_env((len + 1) * sizeof(char),ALLOC);
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
	res = (char *)ft_malloc_env(len + 1 ,ALLOC);
	if (!res)
		return (NULL);
	i = start;
	j = 0;
	while (i < len_str && j < len)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}
t_expand *addnew_expand_node_env(char *key, char *value)
{
	t_expand *new_node = (t_expand *)ft_malloc_env(sizeof(t_expand), ALLOC);
	if (!new_node)
		return NULL;

	new_node->key = ft_strdup_env(key);
	new_node->value = ft_strdup_env(value);
	new_node->next = NULL;
	return new_node;
}

void lstadd_back_expand_env(t_expand **lst, t_expand *new_node)
{
	if (!*lst)
	{
		*lst = new_node;
		return;
	}
	t_expand *last = *lst;
	while (last->next)
		last = last->next;

	last->next = new_node;
}
void ft_free_all_env(t_free *head)
{
	t_free *current = head;
	while (current)
	{
		t_free *next = current->next;

		free(current->add);
		free(current);
		current = next;
	}
	head = NULL;
}

t_free *addnew_free_env(void *add)
{
	t_free *new = malloc(sizeof(t_free));
	if (!new)
		return (NULL);
	new->add = add;
	new->next = NULL;
	return (new);
}
void addback_free_env(t_free **head, t_free *new)
{
	t_free *tmp = *head;
	if (!tmp)
	{
		*head = new;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
void *ft_malloc_env(size_t size, int status)
{
	static t_free *head = NULL;
	t_free *tmp;
	if (status == ALLOC)
	{
		(void)size;
		void *rt = malloc(size);
		if (!rt)
			exit(0);
		tmp = addnew_free_env(rt);
		if (!tmp)
		{
			ft_free_all_env(head);
			exit(0);
		}
		addback_free_env(&head, tmp);
		return (rt);
	}
	else
		return (ft_free_all_env(head), head = NULL);
}
void init_env(t_expand **head, char *env[])
{
	int i;

	char *cmd[] = {"unset", "OLDPWD", NULL};

	i = 0;
	while (env[i])
	{
		int j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		char *key = ft_substr_env(env[i], 0, j);
		char *value = ft_substr_env(env[i], j + 1, ft_strlen(env[i]) - j - 1);
		lstadd_back_expand_env(head, addnew_expand_node_env(key, value));
		i++;
	}
	ft_unset(cmd, head);
	char *cmd2[] = {"export", "OLDPWD", NULL};
	ft_export(cmd2, head);
}