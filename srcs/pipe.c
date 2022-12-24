#include "minishell.h"

int	ft_pipex(t_data *data, t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		ft_runcmd(data, cmd);
	}
	else
	{
		waitpid(pid, &g_status, WNOHANG);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		// if (cmd->next->pipe == 1)
		// 	ft_pipex(data, cmd->next);
		// else
		// 	ft_runcmd(data, cmd->next);
	}
	return (0);
}

int	ft_topipe(t_data *data, t_cmd *cmd)
{
	int		i;
	pid_t	pid;
	t_cmd	*head;

	i = 0;
	head = cmd;
	while (head && head->pipe == 1 && i++ >= 0)
		head = head->next;
	if (cmd->pipe == 1)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			if (cmd->infile != 0)
				dup2(cmd->infile, 0);
			ft_pipex(data, cmd);
			exit(0);
		}
		else
			waitpid(pid, &g_status, 0);
		return (ft_freel1(data, i));
	}
	return (0);
}
