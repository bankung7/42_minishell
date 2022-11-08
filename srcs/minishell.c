#include "minishell.h"

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
            printf("[%d] => %s\n", i, head->cmd);
            head = head->next;
            i++;
        }
        // ===== link list
        printf("\n");
    }
    return (0);
}