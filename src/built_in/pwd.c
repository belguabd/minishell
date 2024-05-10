/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 01:39:25 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 08:42:09 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;
	size_t	len_cpy;

	if (!dstsize && !dst)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	if (dstsize <= dest_len)
		return (dstsize + src_len);
	len_cpy = dstsize - dest_len - 1;
	i = 0;
	while (i < len_cpy && src[i])
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	i;

	len_src = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len_src);
}

t_expand	*get_pwd_cd(t_expand *env)
{
	t_expand	*pwd;

	pwd = env;
	while (pwd)
	{
		if ((ft_strcmp(pwd->key, "PWD") == 0))
			return (pwd);
		pwd = pwd->next;
	}
	return (NULL);
}

char	*ft_get_cwd(char *new_path, int mode)
{
	char		path[PATH_MAX];
	static char	static_path[PATH_MAX];

	if (getcwd(path, PATH_MAX) != NULL)
	{
		ft_strlcpy(static_path, path, PATH_MAX);
		return (static_path);
	}
	if (mode == 1)
	{
		ft_strlcat(static_path, "/", PATH_MAX);
		ft_strlcat(static_path, new_path, PATH_MAX);
	}
	return (static_path);
}

void	ft_pwd(t_expand *env)
{
	char	*path;

	(void)env;
	path = ft_get_cwd(NULL, 0);
	printf("%s\n", path);
}
