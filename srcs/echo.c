#include "minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	nw;

	i = 1;
	nw = 1;
	while (cmd->argv[i] && ft_strncmp("-n", cmd->argv[i], 3) == 0)
	{
		nw = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		// printf("%s", cmd->argv[i++]);
		ft_putstr_fd(cmd->argv[i++], 2);
		if (cmd->argv[i] != 0)
			ft_putchar_fd(' ', 2);
			// printf(" ");
	}
	if (nw == 1)
		ft_putchar_fd('\n', 2);
		// printf("\n");
	return (0);
}
