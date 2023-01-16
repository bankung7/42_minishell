#include "minishell.h"

static int	ft_delenv(t_data *data, int pos)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char *) * ft_arrlen(data->env));
	if (!tmp)
		return (-1);
	while (data->env && data->env[i])
	{
		if (i == pos)
			j++;
		tmp[i] = data->env[i + j];
		i++;
	}
	free(data->env);
	data->env = tmp;
	return (0);
}

static int	ft_checkvar(t_data *data, char *var)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->env && data->env[i])
	{
		tmp = ft_strchr(data->env[i], '=');
		if (ft_strncmp(var, data->env[i], tmp - data->env[i]) == 0)
		{
			ft_delenv(data, i);
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_data *data, t_cmd *cmd, int mode)
{
	int	i;

	if (mode == 1)
		return (0);
	i = 1;
	while (cmd->argv && cmd->argv[i])
		ft_checkvar(data, cmd->argv[i++]);
	g_status = 0;
	return (0);
}
