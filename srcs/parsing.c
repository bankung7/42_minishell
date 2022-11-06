#include "minishell.h"

int ft_cleararray(char **arr, int res)
{
    int i;

    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
    return (res);
}

char **ft_groupcmd(t_token **token)
{
    int i;
    int len;
    char **cmd;
    t_token *head;

    i = 0;
    len = 0;
    head = *token;
    while (head)
    {
        if (head->type != WORD)
            break ;
        len++;
        head = head->next;
    }
    cmd = malloc(sizeof(char*) * (len + 1));
    if (!cmd)
        return (0);
    head = *token;
    while (i < len)
    {
        cmd[i++] = ft_strdup(head->string);
        head = head->next;
    }
    cmd[i] = 0;
    return (cmd);
}

int ft_readtoken(t_token **token)
{
    t_token *head;

    head = *token;
    while (head)
    {
        if (head->type == ERROR_TOKEN)
            return (-1);
        head = head->next;
    }
    return (0);
}

int ft_buildcmd(t_token **token)
{
    pid_t pid;
    char *path;
    char **cmd;

    if (ft_checktoken(token) == -1)
        return (-1);
    if (ft_isbuiltin((*token)->string) != 0)
        return (printf("this is a builtin\n"));
    path = ft_strjoin("/bin/", (*token)->string);
    if (access(path, F_OK) == 0)
    {
        cmd = ft_groupcmd(token);
        pid = fork();
        if (pid == -1)
            return (ft_cleararray(cmd, -1));
        else if (pid == 0)
        {
            execve(path, cmd, 0);
            exit(0);
        }
        else
            wait(0);
        ft_cleararray(cmd, 0);
        free(path);
    }
    else
    {
        free(path);
        return (-1);
    }
    return (0);
}
