#include "../minishell.h"

int main(int argc, char **argv, char **env)
{
    char *cmd[] = {"/bin/cat", NULL};
    int fd = open("file", O_RDONLY, 0777);
    int fd2 = open("file2", O_RDWR | O_CREAT | O_APPEND, 0777);
    int fd3 = open("file3", O_RDWR | O_CREAT | O_APPEND, 0777);

    int pid2 = fork();
    if(pid2 == 0)
    {
        dup2(fd, 0);
        dup2(fd2, 1);
        close(fd);
        close(fd2);
        dup2(fd3, 1);
        write
        execve(cmd[0], cmd, env);
    }
    close(fd);
        close(fd2);
        close(fd3);
    int pid = getpid();

    // Create a buffer to hold the command
    char command[100];
    
    // Construct the command with the PID
    snprintf(command, sizeof(command), "lsof -p %d", (int)pid);

    // Execute the command
    system(command);
}

