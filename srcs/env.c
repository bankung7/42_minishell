#include "minishell.h"

// get variable from environment
char	*ft_getenv(t_data *data, char *var)
{
	int		i;
	int		len;
	char	*value;

	i = 0;
	len = ft_strlen(var);
	while (data->env[i] != 0)
	{
		value = ft_strchr(data->env[i], '=');
		if (len != (value - data->env[i]))
		{
			i++;
			continue ;
		}
		if (value != 0 && ft_strncmp(var, data->env[i],
				value - data->env[i]) == 0)
			return (ft_strdup(value + 1));
		i++;
	}
	return (0);
}

int	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
		printf("%s\n", data->env[i++]);
	g_status = 0;
	return (0);
}
