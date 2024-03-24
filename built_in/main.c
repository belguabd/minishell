/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:44:34 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/21 05:43:25 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

void    f()
{
    system("leaks a.out");
}

int main(int argc, char const *argv[], char *envp[])
{
    int fd;

    fd = open("test", O_WRONLY | O_CREAT, 0777);
    dup2(fd, STDOUT_FILENO);
    printf("hello");
}
