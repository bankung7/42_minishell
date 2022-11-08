#include "minishell.h"

int ft_clearlist(t_mini *data)
{
    if (!data)
        return (0);
    if (data->cmdlist == 0)
        return (0);
    t_cmd *head;
    head = data->cmdlist;
    while (head)
    {
        data->cmdlist = data->cmdlist->next;
        free(head->cmd);
        free(head->path);
        free(head);
        head = data->cmdlist;
    }
    return (0);
}

int main(void)
{
    char *line;
    t_mini *data;

    data = malloc(sizeof(t_mini));
    if (!data)
        return (-1);
    data->cmdlist = 0;
    while (1)
    {
        line = readline(PROMPT);
        if (!line)
            continue;
        ft_tokenize(data, line);
        free(line);
        // ----- link list
        t_cmd *head;

        int i = 0;
        head = data->cmdlist;
        while (head)
        {
            printf("\n========== node [%d] =========\n", i);
            printf("Command :\t[%s]\n", head->cmd);
            printf("Path :\t[%s]\n", head->path);
            printf("Infile :\t[%d]\n", head->infile);
            printf("Outfile :\t[%d]\n", head->outfile);
            printf("Type :\t[%d]\n", head->type);
            printf("==============================\n");
            head = head->next;
            i++;
        }
        if (ft_checkcmd(data) == -1)
            printf("syntax error\n");
        ft_clearlist(data);
        // ===== link list
        printf("\n");
    }
    return (0);
}