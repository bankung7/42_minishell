/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:05:20 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:05:22 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

// print env when no argv
int	ft_printenv(char **env, t_cmd *head)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", head->tfd);
		ft_putstr_fd(env[i], head->tfd);
		ft_putchar_fd('\n', head->tfd);
		i++;
	}
	return (0);
}

// set new variable in environment
int	ft_addenv(t_data *data, char *var)
{
	int		i;
	int		len;
	char	**tmp;

	i = 0;
	len = ft_arrlen(data->env);
	tmp = ft_calloc(sizeof(char *), len + 2);
	if (!tmp)
		return (-1);
	while (i < len)
	{
		tmp[i] = data->env[i];
		i++;
	}
	if (var)
		tmp[i] = ft_strdup(var);
	free(data->env);
	data->env = tmp;
	return (0);
}

// set variable to environment
int	ft_setenv(t_data *data, char *var)
{
	int	i;

	i = 0;
	while (data->env && data->env[i])
	{
		if (ft_strncmp(var, data->env[i], ft_strchr(var, '=') - var) == 0)
		{
			free(data->env[i]);
			data->env[i] = ft_strdup(var);
			return (0);
		}
		i++;
	}
	ft_addenv(data, var);
	return (0);
}

int	ft_export(t_data *data, t_cmd *cmd, int mode)
{
	int	i;

	if (mode == 1)
		return (0);
	i = 1;
	if (cmd->argv[1] == 0)
		return (ft_printenv(data->env, cmd));
	while (cmd->argv && cmd->argv[i])
	{
		if (ft_strchr(cmd->argv[i], '=') != 0)
			ft_setenv(data, cmd->argv[i]);
		i++;
	}
	g_status = 0;
	return (0);
}
