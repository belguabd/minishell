/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:44:34 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/16 01:27:23 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    f()
{
    system("leaks a.out");
}

int main(int argc, char const *argv[], char *envp[])
{
    char *cmd[3];
    cmd[0] = "/bin/ls";
    cmd[1] = "-l";
    cmd[2] = NULL;

    execve(cmd[0], cmd, envp);
}