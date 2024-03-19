/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 21:00:39 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/18 22:07:31 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_execute(char **cmd)
{
    if (ft_strncmp(cmd[0], "cd", 2) == 0)
        ;
    else if (ft_strncmp(cmd[0], "pwd", 3) == 0)
        ft_pwd();
    else if (ft_strncmp(cmd[0], "echo", 4) == 0)
        ft_echo(cmd);
    
}
