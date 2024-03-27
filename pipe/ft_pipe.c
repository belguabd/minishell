/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-bou <soel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:20:36 by soel-bou          #+#    #+#             */
/*   Updated: 2024/03/27 10:57:09 by soel-bou         ###   ########.fr       */
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
    int old_fd_in;
    int old_fd_out;

    head = *cmds;
    while (head)
    {
        tmp = head->redir;
        while(tmp)
        {
            old_fd_out = head->outfile;
            old_fd_in = head->infile;
            if(tmp->type == REDIRECT_OUT)
            {
                head->outfile = open(tmp->value, O_RDWR | O_CREAT | O_TRUNC, 0777);
                if(old_fd_out != head->outfile)
                {
                    close(old_fd_out);
                    old_fd_out = head->outfile;
                }
                if(head->outfile < 0)
                    perror("fd_out");
            }
            else if(tmp->type == REDIRECT_APPEND)
            {
                head->outfile = open(tmp->value, O_RDWR | O_CREAT | O_APPEND, 0777);
                if(old_fd_out != head->outfile)
                {
                    close(old_fd_out);
                    old_fd_out = head->outfile;
                }
                if(head->outfile < 0)
                    perror("fd_app");
            }
            else if(tmp->type == REDIRECT_IN)
            {
                head->infile = open(tmp->value, O_RDWR, 0777);
                if(old_fd_in != head->infile)
                {
                    close(old_fd_in);
                    old_fd_in = head->infile;
                }
                if(head->infile < 0)
                    perror("fd_in");
            }
            tmp = tmp->next;
        }
            
        head = head->next;
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
#include <signal.h>
int main(int argc, char *argv[], char **env)
{
    char *cmd[] = {"/bin/echo","-la", NULL};
    token_node *token = (token_node*)malloc(sizeof(token_node));
    token_node *token2 = (token_node*)malloc(sizeof(token_node));
    token_node *token3 = (token_node*)malloc(sizeof(token_node));
    token->type = REDIRECT_APPEND;
    token->value = "file";
    token->next = token2;
    token2->type = REDIRECT_OUT;
    token2->value = "file3";
    token2->next = token3;
    token3->type = REDIRECT_OUT;
    token3->value = "file4";
    token3->next = NULL;
    t_cmd *head = (t_cmd *)malloc(sizeof(t_cmd));
    head->args = cmd;
    head->isfirst = true;
    head->islast = true;
    head->next = NULL;
    head->redir = token;
    init_fds(&head);
    printf("%d\n", head->outfile);
    printf("%d", head->infile);
    pid_t pid = getpid();

    // Create a buffer to hold the command
    char command[100];
    
    // Construct the command with the PID
    snprintf(command, sizeof(command), "lsof -p %d", (int)pid);

    // Execute the command
    system(command);
    
}
// int main(int argc, char *argv[], char *env[])
// {
//     char *cmd[] = {"/bin/echo","-la", NULL};
//     char *cmd2[] = {"/bin/cat", NULL};
//     char *cmd3[] = {"/bin/ls","-lah", NULL};
//     char *cmd4[] = {"/bin/cat", NULL};
//     int fd = open("test", O_RDWR | O_CREAT | O_TRUNC, 0777);
//     t_cmd head;
//     t_cmd head2;
//     t_cmd head3;
//     t_cmd head4;
//     head.args = cmd;
//     head.infile = 0;
//     head.outfile = fd;
//     head.islast = false;
//     head.isfirst = true;
//     head.next = &head4;
    
//     // head2.args = cmd2;
//     // head2.infile = 0;
//     // head2.outfile = 1;
//     // head2.islast = false;
//     // head2.isfirst = false;
//     // head2.next = &head3;
    
    
//     // head3.args = cmd3;
//     // head3.infile = 0;
//     // head3.outfile = 1;
//     // head3.islast = false;
//     // head3.isfirst = false;
//     // head3.next = &head4;

//     head4.args = cmd4;
//     head4.infile = fd;
//     head4.outfile = 1;
//     head4.islast = true;
//     head4.isfirst = false;
//     head4.next = NULL;
//     pipe_line(&head, NULL, env);
    
// }
