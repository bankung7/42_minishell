#include "minishell.h"

// old it broken -> hide
// static int	ft_delvar(t_data *data, int rindex)
// {
// 	int		i;
// 	int		j;
// 	char	**tmp;
//
// 	i = 0;
// 	j = 0;
// 	while (data->env[i])
// 		i++;
// 	tmp = malloc(sizeof(char *) * i);
// 	if (!tmp)
// 		return (-1);
// 	i = 0;
// 	while (data->env[i])
// 	{
// 		if (i == rindex)
// 			free(data->env[i++]);
// 		tmp[j++] = data->env[i++];
// 	}
// 	tmp[j] = 0;
// 	free(data->env);
// 	data->env = tmp;
// 	return (0);
// }
//
// static int	ft_setvar(t_data *data, char *str)
// {
// 	int		i;
// 	char	*find;
//
// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i++;
// 	find = ft_substr(str, 0, i);
// 	// printf("unset : %s\n", find);
// 	if ((int)ft_strlen(find) == 0)
// 	{
// 		free(find);
// 		return (-1);
// 	}
// 	i = 0;
// 	while (data->env[i] && ft_strncmp(find, data->env[i], ft_strlen(find)) != 0)
// 		i++;
// 	free(find);
// 	if (data->env[i] == 0)
// 		return (-1);
// 	else
// 		ft_delvar(data, i);
// 	return (0);
// }

static int  ft_delenv(t_data *data, int pos)
{
	int i;
	int j;
	char **tmp;

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

static int  ft_checkvar(t_data *data, char *var)
{
	int i;

	i = 0;
	while (data->env && data->env[i])
	{
		char *tmp = ft_strchr(data->env[i], '=');
		if (ft_strncmp(var, data->env[i], tmp - data->env[i]) == 0)
		{
			ft_delenv(data, i);
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_unset(t_data *data, t_cmd *cmd)
{
	int	i;

	i = 1;
	while (cmd->argv && cmd->argv[i])
		ft_checkvar(data, cmd->argv[i++]);
	g_status = 0;
	return (1);
}
