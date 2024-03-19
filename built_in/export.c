/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 01:53:18 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/19 22:47:13 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_export(char **cmd, t_expand **envp)
{
    t_expand *new;

	if (!cmd[1])
        ft_env(cmd, envp);
    new = ft_lst_new(cmd[1], cmd[2]);
    if (!new)
        return ;
    ft_lst_add_back(envp, new);
}