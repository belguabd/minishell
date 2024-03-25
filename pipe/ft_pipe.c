/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:20:36 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/25 04:52:14 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    int fd[2];
    int pid;
    char *str = malloc(6);
    char *cmd[] = {"/bin/ls", NULL};
    char *cmd2[] = {"/usr/bin/grep", "a", NULL};

    pipe(fd);
    pid = fork();
    if (pid < 0)
        exit(1);
    if (pid == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execve("/bin/ls", cmd, envp);
    }
    int pid2 = fork();
    if (pid2 < 0)
        exit(1);
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        execve(cmd2[0], cmd2, envp);
        perror("execve");
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);
    if(pid2 > 0 && pid > 0)
        printf("done");
}

void    run_multi_pipe(char *cmd1[], char *cmd2[], int fd[], char *env[])
{
    int pid1;
    int pid2;

    if (pipe(fd) < 0)
        perror("pipe");
    if ((pid1 = frok()) < 0 || (pid2 =frok()) < 0)
        perror("fork");
    if (pid1 == 0)
    {
        close(fd[1]);
        dup2(1, fd[1]);
        close(fd[1]);
        execve(cmd1[0], cmd1, env);
        perror(cmd1[0]);
    }
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(1, fd[1]);
        close(fd[1]);
        execve(cmd2[0], cmd2, env);
        perror(cmd2[0]);
    }
}