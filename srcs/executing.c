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

// set to cmd where to run
int	ft_where2run(t_cmd *head)
{
	if (head->path == 0)
		return (0);
	if (ft_strncmp("cd", head->argv[0], 3) == 0
		|| ft_strncmp("export", head->argv[0], 7) == 0
		|| ft_strncmp("unset", head->argv[0], 6) == 0
		|| ft_strncmp("exit", head->argv[0], 5) == 0)
		head->pc = 1;
	return (0);
}

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
	if (head->path != 0)
		ft_builtin_out(data, head, 0);
}

static void	child(t_data *data, t_cmd *head)
{
    signal(SIGINT, ft_sigchild);
	heredoc_dup(head);
	stdout_dup(data, head);
	stdin_dup(data, head);
	if (head->pc == 0 && ft_builtin(data, head) == 0)
	{
		if (head->path == 0)
			exit(0);
		ft_runcmd(data, head);
	}
	exit(126);
}

int	ft_waitchild(t_data *data)
{
	int		status;
	t_cmd	*head;

	head = data->cmdlist;
	while (head)
	{
		if (head->next == 0 && head->pc == 0)
		{
			waitpid(head->pid, &status, 0);
			g_status = WEXITSTATUS(status);
		}
		else
			waitpid(head->pid, 0, 0);
		head = head->next;
	}
	return (0);
}

int	ft_execute(t_data *data)
{
	t_cmd	*head;

	if (!data->cmdlist)
		return (-1);
	head = data->cmdlist;
	if (infile_dup(data, head) == -1)
		return (-1);
	while (head)
	{
		ft_where2run(head);
		pipe_next(data, head);
		head->pid = fork();
		if (head->pid == 0)
			child(data, head);
		parent(data, head);
		head = head->next;
	}
	ft_waitchild(data);
	return (0);
}
