#include "minishell.h"

// builtin cmd : echo cd pwd unset export env exit

int ft_isbuiltin(t_cmd *cmd, int x)
{
	int len;

	len = ft_strlen(cmd->argv[0]);
	if (len == 3 && ft_strncmp(cmd->argv[0], "pwd", len + 1) == 0)
	{
		// dprintf(2, "PWD\n");
		return (ft_pwd(x));
	}
	if (len == 4 && ft_strncmp(cmd->argv[0], "echo", len + 1) == 0)
	{
		// dprintf(2, "ECHO\n");
		return (ft_echo(cmd, x));
	}
	if (len == 2 && ft_strncmp(cmd->argv[0], "cd", len + 1) == 0)
	{
		// printf("CD\n");
		return (ft_cd(cmd, x));
	}
	return (-1);
}

int ft_pwd(int x)
{
    char *path;

    if (x == 0)
        return (0);
    path = getcwd(0, 1024);
    ft_putstr_fd(path, 1);
    free(path);
    write(1, "\n", 1);
    return (0);
}

int ft_echo(t_cmd *cmd, int x)
{
    int ferror;
    int newline;
    int space;

    if (x == 0)
        return (0);
    ferror = 0;
    newline = 1;
    space = 0;
    while (cmd->argv[x])
    {
        if (ferror == 0 && ft_strncmp(cmd->argv[x], "-n", 3) == 0)
        {
            newline = 0;
            x++;
            continue ;
        }
        else if (ferror == 0 && ft_strncmp(cmd->argv[x], "-n", 3) != 0)
            ferror = 1;
        if (space++ > 0)
            write(1, " ", 1);
        ft_putstr_fd(cmd->argv[x++], 1);
    }
    if (newline == 1)
        write(1, "\n", 1);
    return (0);
}

int ft_cd(t_cmd *cmd, int x)
{
	if (x == 0)
        return (0);
    return (chdir(cmd->argv[1]));
}
