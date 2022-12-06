#include "minishell.h"

int ft_pipex(t_data *data, t_cmd *cmd)
{
	int fd[2];
	pid_t pid;

	if (pipe(fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		ft_runcmd(data, cmd);
		close(fd[1]);
		exit(0);
	}
	else
	{
		wait(0);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		if (cmd->next->pipe == 1)
			ft_pipex(data, cmd->next);
		else
			ft_runcmd(data, cmd->next);
	}
	return (0);
}

int ft_topipe(t_data *data, t_cmd *cmd)
{
	int i;
	t_cmd *head;
	pid_t pid;

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
			ft_pipex(data, cmd);
			exit(0);
		}
		else
			wait(0);
		return (ft_freel1(data, i));
	}
	return (0);
}

// int	ft_pipex(t_data *data, t_cmd *head)
// {
// 	pid_t	pid;
// 	int		fd[2];

// 	if (pipe(fd) != 0)
// 	{
// 		ft_putstr_fd("Error at pipe.", 2);
// 		return (-1);
// 	}
// 	return (0);
// 	pid = fork();
// 	if (pid < 0)
// 		return (-1);
// 	else if (pid == 0)
// 	{
// 		close(fd[0]);
// 		if (head->next != NULL)
// 			dup2(fd[1], 1);
// 		close(fd[1]);
// 		// execve(head->path, head->argv, 0);
// 		ft_execve(data, head);
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		close(fd[1]);
// 		dup2(fd[0], 0);
// 		close(fd[0]);
// 		head = head->next;
// 		if (head->next != NULL)
// 			ft_pipex(data, head);
// 		else
// 		{
// 			ft_execve(data, head);
// 			exit(0);
// 			return (0);
// 		}
// 	}
// 	return (0);
// }