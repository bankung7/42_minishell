#include "minishell.h"

int ft_clean(t_data *data, int res)
{
    int i;
    t_cmd *head;

    i = 0;
    head = data->cmdlist;
    while (head)
    {
        while (head->argv && head->argv[i])
            free(head->argv[i++]);
        free(head->path);
        free(head->argv);
        head = head->next;
        free(data->cmdlist);
        data->cmdlist = head;
    }
    return (res);
}