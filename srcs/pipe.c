#include "minishell.h"

int	pipe_next(t_data *data, t_cmd *head)
{
	(void) data;
	if (head->next != NULL)
	{
		if (pipe(head->next->pfd) == -1)
		{
			perror("Error in pipe : ");
			return (-1);
		}
		dprintf(2, "PIPE\n");
	}
	return (0);
}

int	infile_dup(t_data *data, t_cmd *head)
{
	(void) data;
	if (head->path == NULL)
	{
		dprintf(2,"path NULL: %d\n", head->infile);
		return (0);
	}
	if (dup2(head->infile, STDIN_FILENO) < 0)
	{
		perror("Error dup file : ");
		return (-1);
	}
	return (0);
}

void	stdout_dup(t_data *data, t_cmd *head)
{
	(void) data;
	if (head->pipe == 1)
	{
		dprintf(2, "%s: close pfds in stdout_dup\n", head->path);
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
	(void)data;
	if (head != data->cmdlist)
	{
		dprintf(2, "%s: close pfds in stdin_dup\n", head->path);
		close(head->pfd[WR]);
		dup2(head->pfd[RD], STDIN_FILENO);
		close(head->pfd[RD]);
	}
}
