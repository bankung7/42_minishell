#include "minishell.h"

int ft_isdelimit(char *str, int i)
{
    if (str[i] == ' ' || str[i] == '\t')
        return (1);
    return (0);
}

int    ft_addtoken(char *str, int i)
{
    int j;
    char *output;

    j = 0;
    output = 0;
    // printf("input [%c]\n", str[i + j]);
    while (str[i + j])
    {
        if (ft_isdelimit(str, i + j) == 0)
            j++;
        else
        {
            output = ft_substr(str, i, j);
            if (!output)
                return (0);
            printf("token : %s=>[%d]\n", output, j);
            free(output);
            return (j);
        }
    }
    if (j > 0)
    {
        output = ft_substr(str, i, j);
        if (!output)
            return (0);
        printf("token : %s=>[%d]\n", output, j);
        free(output);
        return (j);
    }
    return (0);
}

void    ft_token(char *str)
{
    int i;

    i = 0;
    while (str[i] && i < (int)ft_strlen(str))
    {
        // printf("[%d]=>%c\n", i, str[i]);
        if (ft_isdelimit(str, i) == 0)
        {
            i += (ft_addtoken(str, i) - 1);
            // printf("current char %c=\n", str[i]);
        }
        i++;
    }
}