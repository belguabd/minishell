/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:13:58 by belguabd          #+#    #+#             */
/*   Updated: 2024/03/27 14:14:50 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char *ft_strdup(const char *cmd, int start, int end)
// {
// 	int i;
// 	char *new;
// 	int len;
// 	len = end - start;
// 	new = (char *)malloc((len + 1) * sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	i = 0;
// 	while (start < end)
// 		new[i++] = cmd[start++];
// 	new[i] = '\0';
// 	return (new);
// }
char *ft_strdup(const char *s1)
{
	int len;
	int i;
	char *string;

	len = ft_strlen(s1);
	string = (char *)ft_malloc((len + 1) * sizeof(char),ALLOC);
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
