#include "minishell.h"

// check flag
static int	ft_cflag(char *str)
{
	int	i;

	i = 2;
	if (ft_strncmp(str, "-n", 2) != 0)
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	nw;

	i = 1;
	nw = 1;
	while (cmd->argv[i] && cmd->argv[i][0] == '-')
	{
		if (ft_cflag(cmd->argv[i]) == 0)
			nw = 0;
		else
			break ;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr_fd(cmd->argv[i], cmd->outfile);
		if (cmd->argv[i + 1] != 0)
			ft_putchar_fd(' ', cmd->outfile);
		i++;
	}
	if (nw == 1)
		ft_putchar_fd('\n', cmd->outfile);
	return (0);
}
