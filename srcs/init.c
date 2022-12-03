#include "minishell.h"

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
