#include "minishell.h"

int ft_redirection(t_cmd *cmd, char *str)
{
    int fd;

    if (cmd->type == INFILE)
        fd = open(str, O_RDONLY);
    else if (cmd->type == OUTFILE)
        fd = open(str, O_WRONLY | O_TRUNC, 0644);
    else
        fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0644);

    if (fd == -1)
        return (-1);

    if (cmd->type == INFILE)
        cmd->infile = fd;
    else
        cmd->outfile = fd;
    return (0);
}