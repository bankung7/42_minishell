#include "minishell.h"
#include <errno.h>

int ft_ctype(t_data *data)
{

    if (ft_strncmp(&data->line[data->len], ">>", 2) == 0)
        return (APPEND);
    if (ft_strncmp(&data->line[data->len], "<<", 2) == 0)
        return (HEREDOC);
    if (data->line[data->len] == '>')
        return (OUTFILE);
    if (data->line[data->len] == '<')
        return (INFILE);
    if (data->line[data->len] == '|')
        return (PIPE);
    if (data->line[data->len] == ' ' || data->line[data->len] == '\t' || data->line[data->len] == '\n')
        return (DELIMITER);
    if (data->line[data->len] == '\'')
        return (SQUOTE);
    if (data->line[data->len] == '"')
        return (DQUOTE);
    return (100);
}

int ft_cquote(t_data *data, int type)
{
    int i;

    data->len++;
    while (data->line[data->len])
    {
        i = ft_ctype(data);
        if (i == type)
            break;
        data->len++;
    }
    if (data->line[data->len] == 0 && (i != type))
        data->status = -1;
    return (0);
}

int ft_wlexical(t_data *data)
{
    int i;
    int type;

    i = data->len;
    while (data->status == 0 && data->line[data->len])
    {
        type = ft_ctype(data);
        if (type == 11 || type == 12)
            ft_cquote(data, type);
        else if (type <= 5)
            break;
        data->len++;
    }
    if (data->status == 0)
        data->status = ft_addtoken(data, ft_substr(data->line, i, data->len - i), WORD);
    return (data->status);
}

// get schar to token
int ft_slexical(t_data *data, int type)
{
    int len;

    len = ((type + 1) % 2) + 1;
    data->status = ft_addtoken(data, ft_substr(data->line, data->len, len), type);
    data->len += len;
    return (data->status);
}

// check each char and send to tokenize
int ft_lexical(t_data *data)
{
    int type;

    while (data->line[data->len] && data->status == 0)
    {
        type = ft_ctype(data);
        if (type >= 11)
            ft_wlexical(data);
        else if (type >= 1)
            ft_slexical(data, type);
        else
            data->len++;
    }
    // if (data->status != 0)
    // 	printf("quote error\n");
    // ft_ttoken(data);
    // printf("lexical status : %d\n", data->status);
    ft_parser(data);
    return (0);
}

/////////////////////////////

int ft_free2i(int **tmp, int x)
{
    if (!tmp)
        return (0);
    while (--x > 0)
    {
        close(tmp[x][0]);
        close(tmp[x][1]);
        free(tmp[x]);
    }
    free(tmp);
    return (0);
}

int ft_free2a(void **tmp)
{
    int i;

    i = 0;
    if (!tmp)
        return (0);
    while (tmp && tmp[i])
        free(tmp[i++]);
    if (tmp)
        free(tmp);
    return (0);
}

char **ft_envpath(t_data *data)
{
    char *path;
    char **tmp;

    path = ft_getenv(data, "PATH");
    if (!path)
        return (0);
    tmp = ft_split(path, ':');
    free(path);
    if (!tmp)
        return (0);
    return (tmp);
}

int ft_checkcmd(char *cmd)
{
    if (access(cmd, F_OK | X_OK) == 0)
        return (0);
    return (-1);
}

int ft_mpath(t_cmd *head, char **path)
{
    int i;
    char *tmp;

    i = 0;
    if (ft_checkcmd(head->path) == 0)
        return (0);
    while (path && path[i])
    {
        tmp = malloc(sizeof(char) * (ft_strlen(path[i]) + ft_strlen(head->path) + 2));
        if (!tmp)
            return (-1);
        ft_memcpy(tmp, path[i], ft_strlen(path[i]));
        ft_memset(&tmp[ft_strlen(tmp)], '/', 1);
        ft_memcpy(&tmp[ft_strlen(tmp)], head->path, ft_strlen(head->path));
        tmp[ft_strlen(tmp)] = 0;
        if (ft_checkcmd(tmp) == 0)
        {
            free(head->path);
            head->path = tmp;
            return (0);
        }
        i++;
    }
    return (-1);
}

int ft_create_pipe(t_data *data)
{
    t_cmd *head;

    head = ft_lastcmd(data->cmdlist);
    data->tp = head->seq;
    int i;

    i = 0;
    data->pipe = malloc(sizeof(int *) * data->tp);
    while (i < data->tp)
    {
        data->pipe[i] = malloc(sizeof(int) * 2);
        if (!data->pipe[i])
            return (0);
        if (pipe(data->pipe[i]) == -1)
        {
            perror("pipe error\n");
            exit(0);
        }
        i++;
    }
    return (0);
}

int ft_close_pipe(t_data *data)
{
    int i = 0;
    while (i < data->tp)
    {
        close(data->pipe[i][0]);
        close(data->pipe[i][1]);
        i++;
    }
    return (0);
}

int ft_deal_pipe(t_data *data, int i)
{
    t_cmd *head;

    if (!data->cmdlist || !data->cmdlist->next)
        return (0);
    head = data->cmdlist;
    while (head)
    {
        printf("now at %d %d\n", i, head->seq);
        if (head->seq + 1 == i)
        {
            close(data->pipe[head->seq][1]);
            dup2(data->pipe[head->seq][0], STDIN_FILENO);
        }
        else if (head->seq == i)
        {
            close(data->pipe[head->seq][0]);
            dup2(data->pipe[head->seq][1], STDOUT_FILENO);
        }
        else
        {
            close(data->pipe[head->seq][0]);
            close(data->pipe[head->seq][1]);
        }
        head = head->next;
    }
    return (0);
}

int ft_execute1(t_data *data)
{
    t_cmd *head;
    char **path;

    if (data->cmdlist == 0)
        return (-1);
    head = data->cmdlist;
    path = ft_envpath(data);
    ft_create_pipe(data);
    while (data->status == 0 && head)
    {
        head->pid = fork();
        if (head->pid == -1)
            return (-1);
        if (head->pid == 0)
        {
            if (ft_mpath(head, path) == -1)
                exit(-1);
            ft_deal_pipe(data, head->seq);
            execve(head->path, head->argv, data->env);
            perror("error executing\n");
            exit(-1);
        }
        head = head->next;
    }
    ft_close_pipe(data);

    // wait child
    head = data->cmdlist;
    while (head)
    {
        waitpid(head->pid, 0, 0);
        head = head->next;
    }


    // free path env
    ft_free2a((void **)path);
    ft_free2i(data->pipe, data->tp);
    data->tp = 0;
    return (0);
}
