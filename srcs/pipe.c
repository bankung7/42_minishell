/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:03:28 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:03:33 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_next(t_data *data, t_cmd *head)
{
	(void) data;
	ft_where2run(head);
	if (head->next != NULL)
	{
		if (pipe(head->next->pfd) == -1)
		{
			ft_putstr_fd("Error at pipe\n", 2);
			return (-1);
		}
	}
	return (0);
}

int	infile_dup(t_data *data, t_cmd *head)
{
	(void) data;
	if (dup2(head->infile, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		return (-1);
	}
	return (0);
}

void	stdout_dup(t_data *data, t_cmd *head)
{
	(void) data;
	if (head->pipe == 1)
	{
		close(head->next->pfd[RD]);
		if (head->outfile == 1)
			dup2(head->next->pfd[WR], STDOUT_FILENO);
		else
			dup2(head->outfile, STDOUT_FILENO);
		close(head->next->pfd[WR]);
	}
}

void	stdin_dup(t_data *data, t_cmd *head)
{
	(void) data;
	if (head != data->cmdlist)
	{
		close(head->pfd[WR]);
		dup2(head->pfd[RD], STDIN_FILENO);
		close(head->pfd[RD]);
	}
}
