/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:20:36 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/25 09:26:21 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    int fd[2];
    int fd_in;
    int pid;
    char *str = malloc(6);
    char *cmd[] = {"/usr/bin/cd","..", NULL};
    char *cmd2[] = {"/bin/ls","-l", NULL};
    char *cmd3[] = {"/usr/bin/grep","a", NULL};

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
    close(fd[1]);
    fd_in = fd[0];
    pipe(fd);

    int pid2 = fork();
    if (pid2 < 0)
        exit(1);
    if (pid2 == 0)
    {
        dup2(fd_in, 0);
        close(fd_in);
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execve(cmd2[0], cmd2, envp);
        perror("execve2");
    }
    close(fd_in);
    close(fd[1]);
    fd_in = fd[0];
    int pid3 = fork();
    if (pid3 < 0)
        exit(1);
    if (pid3 == 0)
    {
        dup2(fd_in, 0);
        close(fd_in);
        execve(cmd3[0], cmd3, envp);
        perror("execve3");
    }
    close(fd_in);
    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);
        printf("done");
}

// void    run_multi_pipe(char *cmd1[], char *cmd2[], int fd[], char *env[])
// {
//     int pid1;
//     int pid2;

//     if (pipe(fd) < 0)
//         perror("pipe");
//     if ((pid1 = frok()) < 0 || (pid2 =frok()) < 0)
//         perror("fork");
//     if (pid1 == 0)
//     {
//         close(fd[1]);
//         dup2(1, fd[1]);
//         close(fd[1]);
//         execve(cmd1[0], cmd1, env);
//         perror(cmd1[0]);
//     }
//     if (pid2 == 0)
//     {
//         close(fd[1]);
//         dup2(1, fd[1]);
//         close(fd[1]);
//         execve(cmd2[0], cmd2, env);
//         perror(cmd2[0]);
//     }
// }

// void    pipe_it(t_cmd *cmd, char *env[])
// {
//     int fd[2];
//     int pid;

//     while(cmd)
//     {
//         pipe(fd);
//         pid = fork();
//         if(pid == 0)
//         {
//             if(cmd->next)
//                 dup2(fd[1], 1);
//             close(fd[1]);
//         }
//     }
// }