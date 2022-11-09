#include "minishell.h"

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

t_cmd *ft_newcmd(void)
{
    t_cmd *node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return (0);
    node->vector = 0;
    node->cmd = 0;
    node->path = 0;
    node->infile = 0;
    node->outfile = 1;
    node->type = 0;
    node->next = 0;
    return (node);
}

int ft_buildword(t_mini *data, char *str)
{
	char **atmp;
	t_cmd *head;

	if (!data->cmdlist)
		data->cmdlist = ft_newcmd();
	head = data->cmdlist;
    if (!head)
    {
        ft_clearlist(data);
        return (ft_strlen(str));
    }
	while (head->next)
		head = head->next;
	if (head->type == INFILE)
		head->infile = 99; // handler fd
	else if (head->type == OUTFILE || head->type == APPEND)
		head->outfile = 99; // handler fd
	else
	{
		atmp = ft_cmdarray(head->vector, str);
		head->vector = atmp;
		if (!head->path)
			head->path = ft_strdup(str);
	}
	head->type = 0;
	return (0);
}

int ft_buildfd(t_mini *data, char *str, int type)
{
    int len;
	t_cmd *head;

	if (!data->cmdlist)
		data->cmdlist = ft_newcmd();
	head = data->cmdlist;
    if (!head || (head->type >= 1 && head->type <= 6))
    {
        ft_clearlist(data);
        return (ft_strlen(str));
    }
	while (head->next)
		head = head->next;
	if (type == INFILE)
        head->infile = 99; // set fd later
    else if (type == OUTFILE)
        head->outfile = 99; // set fd later
    else if (type == APPEND)
        head->outfile = 98; // set fd later
    head->type = type;
    len = type % 2;
    if (len == 0)
        len = 2;
    // wait for here doc
	return (len);
}

int ft_buildpipe(t_mini *data, char *str)
{
    t_cmd *node;
    t_cmd *head;

    if (!data->cmdlist)
        return (ft_strlen(str));
    head = data->cmdlist;
    while (head->next)
        head = head->next;
    if (head->type != 0)
    {
        ft_clearlist(data);
        return (ft_strlen(str));
    }
    node = ft_newcmd();
    if (!node)
    {
        ft_clearlist(data);
        return (ft_strlen(str));
    }
    head->next = node;
    return (1);
}