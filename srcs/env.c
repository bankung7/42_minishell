#include "minishell.h"

char *ft_getenv(t_data *data, char *var)
{
    int i;
    char *tmp;
    char *search;

    i = 0;
    search = ft_strjoin(var, "=");
    while (data->env[i])
    {
        if (ft_strncmp(search, data->env[i], ft_strlen(search)) == 0)
        {
            tmp = ft_substr(ft_strchr(data->env[i], '=') + 1, 0, ft_strlen(data->env[i]));
            free(search);
            return (tmp);
        }
        i++;
    }
    free(search);
    return (0);
}