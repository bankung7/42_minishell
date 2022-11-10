#include "minishell.h"

// builtin cmd : echo cd pwd unset export env exit

int ft_isbuiltin(t_cmd *cmd, int xcmd)
{
	int len;

	len = ft_strlen(cmd->path);
	if (len == 4 && ft_strncmp(cmd->path, "echo", len + 1) == 0)
		return (ft_echo(cmd, xcmd));
    if (len == 3 && ft_strncmp(cmd->path, "pwd", len + 1) == 0)
		return (ft_pwd(xcmd));
    if (len == 3 && ft_strncmp(cmd->path, "env", len + 1) == 0)
		return (ft_env(xcmd));
	return (-1);
}

int ft_echo(t_cmd *cmd, int xcmd)
{
    int i;
    int nl;

    i = 1;
    nl = 0;
    if (xcmd == 0)
        return (0);
    // how to deal with flag
    if (cmd->vector && ft_strncmp(cmd->vector[i], "-n", 3) == 0)
    {
        nl = 1;
        i++;
    }
    while (cmd->vector[i])
    {
        if (i - nl > 1)
            write(1, " ", 1);
        ft_putstr_fd(cmd->vector[i++], 1);
    }
    if (nl == 0)
        write(1, "\n", 1);
    return (0);
}

int ft_pwd(int xcmd)
{
    char *buf;
    char *path;
    
    if (xcmd == 0)
        return (0);
    buf = malloc(sizeof(char) * 1024);
    if (!buf)
        return (-1);
    path = getcwd(buf, 1024);
    ft_putstr_fd(path, 1);
    free(path);
    return (0);
}

int ft_env(int xcmd)
{
    if (xcmd == 0)
        return (0);
    // how to deal with all variable
    printf("%s\n", getenv("PATH"));
    return (0);
}