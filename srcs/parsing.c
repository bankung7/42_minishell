#include "minishell.h"

int ft_isbuiltin(char *str)
{
    int len;

    len = ft_strlen(str);
    if (len == 2 && ft_strncmp("cd", str, 2) == 0)
        return (printf("builtin cd\n"));
    else if (len == 3 && ft_strncmp("pwd", str, 3) == 0)
        return (printf("builtin pwd\n"));
    else if (len == 3 && ft_strncmp("env", str, 3) == 0)
        return (printf("builtin env\n"));
    else if (len == 4 && ft_strncmp("echo", str, 4) == 0)
        return (printf("builtin echo\n"));
    else if (len == 4 && ft_strncmp("exit", str, 4) == 0)
        return (printf("builtin exit\n"));
    else if (len == 5 && ft_strncmp("unset", str, 5) == 0)
        return (printf("builtin unset\n"));
    else if (len == 6 && ft_strncmp("export", str, 6) == 0)
        return (printf("builtin export\n"));
    return (0);
}

char *ft_trimcmd(char *str)
{
    int len;
    char c;
    char *tmp;

    if (!str)
        return (0);
    if (str[0] == '\'' || str[0] == '"')
    {
        c = str[0];
        len = ft_strlen(str);
        if (str[len - 1] == c)
            tmp = ft_substr(str, 1, len - 2);
        else
            tmp = 0;
    }
    else
        tmp = ft_strdup(str);
    return (tmp);
}

char **ft_cmdarray(char **input, char *arg)
{
    int i;
    int len;
    char **tmp;

    i = 0;
    len = 0;
    if (!input)
    {
        tmp = malloc(sizeof(char *) * 2);
        if (!tmp)
            return (0);
        tmp[0] = ft_strdup(arg);
        tmp[1] = 0;
    }
    else
    {
        while (input[len])
            len++;
        tmp = malloc(sizeof(char *) * (len + 2));
        if (!tmp)
            return (0);
        while (i < len)
        {
            tmp[i] = ft_strdup(input[i]);
            free(input[i]);
            i++;
        }
        tmp[i++] = ft_strdup(arg);
        tmp[i] = 0;
        free(input);
    }
    return (tmp);
}

int ft_iscmd(char *str)
{
    char *tmp;

    // not built-in
    if (ft_isbuiltin(str) == 0)
    {
        tmp = ft_strjoin("/bin/", str);
        if (access(tmp, F_OK) != -1)
        {
            printf("this is a shell command\n");
            return (0);
        }
        else
            return (-1);
    }
    return (0);
}

int ft_buildlist(t_mini *data, char *str, int type)
{
    t_cmd *node;
    t_cmd *head;

    if (!data->cmdlist)
    {
        node = malloc(sizeof(t_cmd));
        if (!node)
            return (-1);
        node->vector = 0;
        node->cmd = 0;
        node->path = 0;
        node->infile = 0;
        node->outfile = 1;
        node->type = 0;
        node->next = 0;
        data->cmdlist = node;
    }

    // current the node
    head = data->cmdlist;
    while (head->next)
        head = head->next;

    if (type == INFILE)
        head->type = INFILE;
    else if (type == OUTFILE)
        head->type = OUTFILE;
    else if (type == APPEND)
        head->type = APPEND;
    else if (type == WORD && head->type == INFILE)
    {
        head->infile = 99; // set fd later
        head->type = 0;
    }
    else if (type == WORD && (head->type == OUTFILE || head->type == APPEND))
    {
        head->outfile = 99; // set fd later
        head->type = 0;
    }
    else if (type == WORD && head->path == 0)
    {
        head->vector = ft_cmdarray(0, str);
        head->cmd = ft_strdup(str);
        head->path = ft_strdup(str);
    }
    else if (type == WORD)
    {
        char *tmp;
        tmp = ft_strjoin(head->cmd, str);
        free(head->cmd);
        head->cmd = ft_strdup(tmp);
        free(tmp);

        char **atmp;
        atmp = ft_cmdarray(head->vector, str);
        head->vector = atmp;
    }
    else if (type == PIPE)
    {
        node = malloc(sizeof(t_cmd));
        if (!node)
            return (-1);
        node->cmd = 0;
        node->path = 0;
        node->infile = 0;
        node->outfile = 1;
        node->type = 0;
        node->next = 0;
        head->next = node;
    }
    return (0);
}

int ft_checkcmd(t_mini *data)
{
    t_cmd *head;

    head = data->cmdlist;
    if (!head)
        return (-1);
    while (head)
    {
        if (ft_iscmd(head->path) == -1)
            return (-1);
        head = head->next;
    }
    return (0);
}