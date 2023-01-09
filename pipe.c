#include "stdio.h"
#include "unistd.h"
#include "sys/wait.h"
#include "stdlib.h"

typedef struct s_token
{
    char *str;
    int pid;
    int pipe[2];
    struct s_token *next;
} t_token;

int ft_build(t_token *token, char **argv)
{
    
    return (0);
}

int main(int argc, char **argv)
{
    int p1[2];
    int p2[2];
    pid_t pid[3];

    if (argc != 4)
        return (-1);
    if (pipe(p1) == -1)
    {
        perror("pipe 1 error\n");
        return (-1);
    }

    if (pipe(p2) == -1)
    {
        perror("pipe 2 error\n");
        return (-1);
    }

    // fork process 1
    pid[0] = fork();
    if (pid[0] == -1)
    {
        perror("child 1 error\n");
        exit(1);
    }
    if (pid[0] == 0)
    {
        printf("do 1\n");
        // close unused pipe
        close(p1[0]);
        dup2(p1[1], STDOUT_FILENO);

        close(p2[0]);
        close(p2[1]);

        execlp(argv[1], argv[1], NULL);
        perror("execute 1 error\n");
        exit(-1);
    }

    pid[1] = fork();
    if (pid[1] == -1)
    {
        perror("child 2 error\n");
        exit(-1);
    }
    if (pid[1] == 0)
    {
        printf("do 2\n");

        dup2(p1[0], STDIN_FILENO);
        close(p1[1]);

        close(p2[0]);
        dup2(p2[1], STDOUT_FILENO);

        execlp(argv[2], argv[2], NULL);
        perror("execute 2 error\n");
        exit(-1);
    }

    pid[2] = fork();
    if (pid[2] == -1)
    {
        perror("child 3 error\n");
        exit(-1);
    }
    if (pid[2] == 0)
    {
        printf("do 3\n");

        close(p1[0]);
        close(p1[1]);
        close(p2[1]);

        dup2(p2[0], STDIN_FILENO);
        execlp(argv[3], argv[3], NULL);
        perror("execute 3 error\n");
        exit(-1);
    }

    // close all pipe in parent
    close(p1[0]);
    close(p1[1]);
    close(p2[0]);
    close(p2[1]);

    // wait pid
    waitpid(pid[0], 0, 0);
    waitpid(pid[1], 0, 0);
    waitpid(pid[2], 0, 0);
    return (0);
}