/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:17:07 by pjerddee          #+#    #+#             */
/*   Updated: 2023/01/10 01:18:57 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent(t_data *data, t_cmd *head)
{
	if (head != data->cmdlist)
	{
		close(head->pfd[WR]);
		close(head->pfd[RD]);
	}
	if (head->hd_lmt != NULL)
	{
		close(head->hdfd[WR]);
		close(head->hdfd[RD]);
	}
	ft_builtin_out(data, head);
}

static void	child(t_data *data, t_cmd *head)
{
	heredoc_dup(head);
	stdout_dup(data, head);
	stdin_dup(data, head);
	if (ft_builtin(data, head) == 0)
		ft_runcmd(data, head);
	exit(0);
}

int	ft_execute(t_data *data)
{
	t_cmd	*head;

	if (!data->cmdlist || data->status != 0)
		return (-1);
	head = data->cmdlist;
	if (infile_dup(data, head) == -1)
		return (-1);
	while (head)
	{
		pipe_next(data, head);
		head->pid = fork();
		if (head->pid == 0)
			child(data, head);
		parent(data, head);
		head = head->next;
	}
	while (wait(&g_status) != -1 || errno != ECHILD)
		;
	return (0);
}
