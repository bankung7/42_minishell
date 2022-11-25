#include "minishell.h"

int ft_prompt(t_data *data)
{
    char *line;

    while (1)
    {
        line = readline(MPROMPT);
        if (!line)
            break ;
        if (ft_strlen(line) == 0)
            continue ;
        // printf("%s\n", line);

        ft_tokenize(data, line);
        ft_expander(data);
        //// test

        int i = 0;

        while (data->tray[i])
            printf("[%s] ", data->tray[i++]);
        printf("\n");

        i = 0;
        while (data->tray[i])
            free(data->tray[i++]);
        free(data->tray);
        data->tray = 0;

        //// test

        free(line);
    }
    return (0);
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_data  data;

    data.cmdlist = 0;
    data.env = env;
    data.tray = 0;
    // ft_sighandle();
    ft_prompt(&data);
    return (0);
}