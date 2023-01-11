#include "minishell.h"

int	ft_resetdata(t_data *data)
{
	data->cmdlist = 0;
	data->line = 0;
	data->len = 0;
	data->status = 0;
	data->token = 0;
	data->ori_fd[RD] = dup(STDIN_FILENO);
	data->ori_fd[WR] = dup(STDOUT_FILENO);
	return (0);
}

int	ft_initenv(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	if (i == 0)
		return (-1);
	data->env = malloc(sizeof(char *) * (i + 1));
	if (!data->env)
		return (-1);
	data->env[--i] = 0;
	while (--i >= 0)
		data->env[i] = ft_strdup(env[i]);
	return (0);
}	
