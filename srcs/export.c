#include "minishell.h"

static int	ft_addenv(t_data *data, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	while (data->env[i])
		i++;
	i += 2;
	tmp = malloc(sizeof(char *) * i);
	if (!tmp)
		return (-1);
	tmp[--i] = 0;
	tmp[--i] = ft_strdup(str);
	while (--i >= 0)
		tmp[i] = data->env[i];
	free(data->env);
	data->env = tmp;
	return (0);
}

static int	ft_setvar(t_data *data, char *str)
{
	int		i;
	char	*find;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	find = ft_substr(str, 0, i);
	if ((int)ft_strlen(find) == 0)
	{
		free(find);
		return (-1);
	}
	i = 0;
	while (data->env[i] && ft_strncmp(find, data->env[i], ft_strlen(find)) != 0)
		i++;
	free(find);
	if (data->env[i] == 0)
		ft_addenv(data, str);
	else
	{
		free(data->env[i]);
		data->env[i] = ft_strdup(str);
	}
	return (0);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv && cmd->argv[i])
	{
		if (ft_strchr(cmd->argv[i], '=') != 0)
			ft_setvar(data, cmd->argv[i]);
		i++;
	}
	g_status = 0;
	return (1);
}
