#include "minishell.h"

int ft_checkcmd(t_mini *data)
{
	t_cmd *head;

	head = data->cmdlist;
	// if (!head)
	// 	return (-1);
	while (head)
	{
		if (ft_isbuiltin(head, 0) == 0)
			head->type = BUILTIN;
		else if (ft_iscmd(data, head->path, head) == 0)
		{
			head->type = COMMAND;
		}
		// else
		// 	return (-1);
		head = head->next;
	}
	return (0);
}

int	ft_iscmd(t_mini *data, char *str, t_cmd *head)
{
	int		i;
	int		status;
	char	*tmp1;
	char	*tmp2;
	char	**path;
	(void)	data;

	i = 0;
	if (access(str, X_OK | R_OK | F_OK) == 0)
		return (0);
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		tmp1 = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp1, str);
		free(tmp1);
		status = access(tmp2, X_OK | R_OK | F_OK);
		if (status == 0)
		{
			head->path = ft_strdup(tmp2);
			return (status);
		}
		free(tmp2);
		i++;
	}
	return (status);
}

int ft_runcmd(t_mini *data)
{
	pid_t pid;
	t_cmd *head;

	if (!data->cmdlist)
		return (-1);
	head = data->cmdlist;
	while (head)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		else if (pid == 0)
		{
			if (head->type == BUILTIN)
				ft_isbuiltin(head, 1);
			else
			{
				// char *path;
				// path = ft_strjoin("/bin/", head->path);
				execve(head->path, head->argv, 0);
				// free(path);
			}
			exit(0);
		}
		else
			wait(0);
		head = head->next;
	}
	return (0);
}
