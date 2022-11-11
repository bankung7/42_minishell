#include "minishell.h"

void    ft_cleararr(void **arr)
{
    int i;

    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

int ft_clearlist(t_mini *data, int res)
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
        if (head->argv)
            ft_cleararr((void**)head->argv);
        free(head->path);
        free(head);
        head = data->cmdlist;
    }
    return (res);
}