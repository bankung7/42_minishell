#include "minishell.h"

// builtin cmd : echo cd pwd unset export env exit
int ft_isbuiltin(char *cmd)
{
    int len;

    len = ft_strlen(cmd);
    if (len == 2 && ft_strncmp("cd", cmd, 2) == 0)
        return (printf("builtin cd\n"));
    else if (len == 3 && ft_strncmp("pwd", cmd, 3) == 0)
        return (printf("builtin pwd\n"));
    else if (len == 3 && ft_strncmp("env", cmd, 3) == 0)
        return (printf("builtin env\n"));
    else if (len == 4 && ft_strncmp("echo", cmd, 4) == 0)
        return (printf("builtin echo\n"));
    else if (len == 4 && ft_strncmp("exit", cmd, 4) == 0)
        return (printf("builtin exit\n"));
    else if (len == 5 && ft_strncmp("unset", cmd, 5) == 0)
        return (printf("builtin unset\n"));
    else if (len == 6 && ft_strncmp("export", cmd, 6) == 0)
        return (printf("builtin export\n"));
    return (0);
}