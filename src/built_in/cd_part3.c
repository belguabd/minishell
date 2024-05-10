/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_part3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 05:31:22 by soel-bou          #+#    #+#             */
/*   Updated: 2024/05/10 08:41:40 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_change_oldpwd(t_expand *oldpwd, t_expand *env, char *op)
{
	oldpwd = get_oldpwd(env);
	if (oldpwd)
	{
		if (oldpwd->value)
		{
			oldpwd->value = NULL;
		}
		oldpwd->value = ft_strdup_env(op);
		oldpwd->isnull = false;
	}
}

void	ft_change_pwd(t_expand *new_pwd, t_expand *env, char *np)
{
	new_pwd = get_pwd(env);
	if (new_pwd)
	{
		if (new_pwd->value)
		{
			new_pwd->value = NULL;
		}
		new_pwd->value = ft_strdup_env(np);
		new_pwd->isnull = false;
	}
}
