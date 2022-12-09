#include "minishell.h"

int	ft_cd(t_cmd *cmd)
{
	return (chdir(cmd->argv[1]));
}
