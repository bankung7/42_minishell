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
	if (head->pipe == 1)
	{
		close(head->pfd[WR]);
		close(head->pfd[RD]);
	}
	if (head->path != NULL)
		ft_builtin_out(data, head, 0);
}

static void	child(t_data *data, t_cmd *head)
{
	stdout_dup(data, head);
	stdin_dup(data, head);
	if (head->path == NULL)
		exit(0);
	if (ft_builtin(data, head) == 0)
		ft_runcmd(data, head);
	exit(0);
}

static void	ft_wait(t_data *data)
{
	t_cmd	*head;

	head = data->cmdlist;
	while (head)
	{
		if (head->next == NULL && ft_builtin_out(data, head, 1) == 0)
			waitpid(head->pid, NULL, 0);
		else
		{
			waitpid(head->pid, &g_status, 0);
			g_status = WEXITSTATUS(g_status);
		}
		head = head->next;
	}
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
		// if (head->path != 0)
		{
			pipe_next(data, head);
			head->pid = fork();
			if (head->pid == 0)
				child(data, head);
			parent(data, head);
		}
		head = head->next;
	}
	ft_wait(data);
	return (0);
}
