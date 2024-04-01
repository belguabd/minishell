/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:44:34 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/28 06:58:10 by soel-bou         ###   ########.fr       */
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
    int fd2;

    fd = open("test", O_WRONLY | O_CREAT, 0777);
    fd2 =open("test", O_WRONLY, 0777);
    printf("%d %d", fd, fd2);
}
