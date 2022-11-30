#include "minishell.h"

int ft_echo(t_cmd *cmd)
{
	int i;
	int nw;

	i = 1;
	nw = 1;
	while (cmd->argv[i] && ft_strncmp("-n", cmd->argv[i], 2) == 0)
	{
		nw = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i++]);
		if (cmd->argv[i] != 0)
			printf(" ");
	}
	if (nw == 1)
		printf("\n");
	return (0);
}