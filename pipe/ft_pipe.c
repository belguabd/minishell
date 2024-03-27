/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:20:36 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/27 08:08:59 by soel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int main(int argc, char *argv[], char *envp[])
// {
//     int fd[2];
//     int fd_in;
//     int pid;
//     char *str = malloc(6);
//     char *cmd[] = {"/bin/echoooo",">>", "f1", NULL};
//     char *cmd2[] = {"/bin/pwd", NULL};
//     char *cmd3[] = {"/usr/bin/grep","o", NULL};

//     pipe(fd);
//     pid = fork();
//     if (pid < 0)
//         exit(1);
//     if (pid == 0)
//     {
//         close(fd[0]);
//         dup2(fd[1], 1);
//         close(fd[1]);
//         execve("/bin/echoooo", cmd, envp);
//         perror(cmd[0]);
//     }
//     close(fd[1]);
//     fd_in = fd[0];
//     pipe(fd);

//     int pid2 = fork();
//     if (pid2 < 0)
//         exit(1);
//     if (pid2 == 0)
//     {
//         dup2(fd_in, 0);
//         close(fd_in);
//         dup2(fd[1], 1);
//         close(fd[0]);
//         close(fd[1]);
//         execve(cmd2[0], cmd2, envp);
//         perror("execve2");
//     }
//     close(fd_in);
//     close(fd[1]);
//     fd_in = fd[0];
//     int pid3 = fork();
//     if (pid3 < 0)
//         exit(1);
//     if (pid3 == 0)
//     {
//         dup2(fd_in, 0);
//         close(fd_in);
//         execve(cmd3[0], cmd3, envp);
//         perror("execve3");
//     }
//     close(fd_in);
//     waitpid(pid, NULL, 0);
//     waitpid(pid2, NULL, 0);
//     waitpid(pid3, NULL, 0);
//         printf("done");
// }

void    init_fds(t_cmd **cmds)
{
    t_cmd *head;
    token_node *tmp;

    head = *cmds;
    while (cmds)
    {
        tmp = head->redir;
        while(tmp)
        {
            if(tmp->type == 0)
        }
    }
}

int get_fd_out(token_node *node)
{
    int fd;
    token_node *tmp;

    while(tmp)
    {
        
    }
}


void    pipe_line(t_cmd *cmd, t_expand *env_lst, char *env[])
{
    int fd[2];
    int tmp_fd_in;
    int pid;

    tmp_fd_in = 0;
    while (cmd)
    {
        pipe(fd);
        pid = fork();
        if(pid < 0)
            perror("fork");
        if(pid == 0)
        {
            if(cmd->infile != 0)
            {
                dup2(cmd->infile, 0);
                close(cmd->infile);
            }
            if(cmd->outfile != 1)
            {
                dup2(cmd->outfile, 1);
                close(cmd->outfile);
            }
            if (!cmd->isfirst)
            {
                dup2(tmp_fd_in, 0);
                close(tmp_fd_in);
            }
            if (!cmd->islast)
            {
                dup2(fd[1], 1);
                close(fd[1]);
                close(fd[0]);
            }
            //execve(cmd->args[0], cmd->args, env);
            ft_execute_node(cmd->args, NULL, env);
            //perror(cmd->args[0]);
        }
        if(!cmd->isfirst)
            close(tmp_fd_in);
        if(!cmd->islast)
        {
            close(fd[1]);
            tmp_fd_in = fd[0];
        }
        cmd = cmd->next;
    }
    int i = 0;
    while(i < 3)
    {
        wait(NULL);
        i++;
    }
}

int main(int argc, char *argv[], char *env[])
{
    char *cmd[] = {"/bin/echo","-la", NULL};
    char *cmd2[] = {"/bin/cat", NULL};
    char *cmd3[] = {"/bin/ls","-lah", NULL};
    char *cmd4[] = {"/bin/cat", NULL};
    int fd = open("test", O_RDWR | O_CREAT | O_TRUNC, 0777);
    t_cmd head;
    t_cmd head2;
    t_cmd head3;
    t_cmd head4;
    head.args = cmd;
    head.infile = 0;
    head.outfile = fd;
    head.islast = false;
    head.isfirst = true;
    head.next = &head4;
    
    // head2.args = cmd2;
    // head2.infile = 0;
    // head2.outfile = 1;
    // head2.islast = false;
    // head2.isfirst = false;
    // head2.next = &head3;
    
    
    // head3.args = cmd3;
    // head3.infile = 0;
    // head3.outfile = 1;
    // head3.islast = false;
    // head3.isfirst = false;
    // head3.next = &head4;

    head4.args = cmd4;
    head4.infile = fd;
    head4.outfile = 1;
    head4.islast = true;
    head4.isfirst = false;
    head4.next = NULL;
    pipe_line(&head, NULL, env);
    
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