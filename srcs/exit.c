/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:05:25 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:05:25 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_clean(t_data *data, int res)
{
	t_cmd	*head;

	ft_freetoken(data, res);
	if (data->cmdlist == 0)
		return (res);
	head = data->cmdlist;
	while (head)
	{
		ft_freecmd(head, 0);
		head = head->next;
		free(data->cmdlist);
		data->cmdlist = head;
	}
	ft_closefd(data, res);
	data->cmdlist = 0;
	return (res);
}

static int	ft_checkargv(t_cmd *cmd)
{
	int	i;

	g_status = 0;
	if (cmd != 0 && cmd->argv[1] != NULL)
	{
		i = 0;
		while (cmd->argv[1][i])
		{
			if (ft_isdigit(cmd->argv[1][i++]) == 0)
			{
				ft_putstr_fd("numeric argument required\n", 2);
				exit(255);
			}
		}
		g_status = ft_atoi(cmd->argv[1]);
	}
	return (0);
}

int	ft_exit(t_data *data, t_cmd *cmd, int mode)
{
	int	i;

	if (mode == 1)
		return (0);
	if (cmd != 0 && ft_arrlen(cmd->argv) > 2)
	{
		ft_putstr_fd("exit\ntoo many arguments\n", 2);
		g_status = 1;
		return (0);
	}
	ft_checkargv(cmd);
	i = 0;
	if (data->iflst != 0)
		return (0);
	ft_clean(data, 0);
	while (data->env && data->env[i])
		free(data->env[i++]);
	free(data->env);
	rl_clear_history();
	printf("exit\n");
	exit(g_status);
	return (0);
}
