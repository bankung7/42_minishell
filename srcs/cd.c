#include "minishell.h"

int	ft_cd(t_cmd *cmd)
{
	g_status = 0;
	return (chdir(cmd->argv[1]));
}
