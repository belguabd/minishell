/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 02:00:07 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/10 08:44:59 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	len_str;

	if (!s)
		return (NULL);
	len_str = ft_strlen(s);
	if (start >= len_str)
		return (ft_strdup(""));
	if (len_str < len + start)
		len = len_str - start;
	res = (char *)ft_malloc(len + 1, ALLOC);
	if (!res)
		return (NULL);
	i = start;
	j = 0;
	while (i < len_str && j < len)
		res[j++] = s[i++];
	res[j] = '\0';
	return (res);
}
