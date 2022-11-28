#include "minishell.h"

void	ft_freesplit(char **str);
int	ft_pipex(t_cmd *head);

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
        else if (ft_iscmd(head->path) != NULL)
            head->type = COMMAND;
		head = head->next;
	}
	return (0);
}

char *ft_iscmd(char *str)
{
	int		i;
	char	*tmp1;
	char	*tmp2;
	char	**path;

	i = 0;
	tmp2 = NULL;
	if (access(str, X_OK | R_OK | F_OK) == 0)
		return (str);
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		tmp1 = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp1, str);
		free(tmp1);
		if (access(tmp2, X_OK | R_OK | F_OK) == 0)
			break ;
		i++;
	}
	ft_cleararr((void **)path);
	if (access(tmp2, X_OK | R_OK | F_OK) == 0)
		return(tmp2);
	else
		return (NULL);
}

int ft_runcmd(t_mini *data)
{
	// int		fd[2];
	pid_t	pid;
	t_cmd	*head;

	if (!data->cmdlist)
		return (-1);
	head = data->cmdlist;
	// if (head->next != NULL)
	// 	ft_pipex(head);
	while (head)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		else if (pid == 0)
		{
			if (head->next == NULL)
				execve(ft_iscmd(head->path), head->argv, 0);
			else
			{
				ft_pipex(head);
				break ;
			}
		}
		else
			wait(NULL);
		head = head->next;
	}
	return (0);
}

int	ft_pipex(t_cmd *head)
{
	pid_t	pid;
	int		fd[2];
	(void)	head;

	printf("In pipex...\n");
	if (pipe(fd) != 0)
	{
		ft_putstr_fd("Error at pipe.", 2);
		return (-1);
	}
	printf("Done piping..\n");
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		close(fd[0]);
		// if (head->next != NULL)
			dup2(fd[1], 1);
		close(fd[1]);
		execve(ft_iscmd(head->path), head->argv, 0);
	}
	else
	{
		wait(NULL);
		// close(fd[1]);
	// 	dup2(fd[0], 0);
	// 	// if (++i < ac - 2)
	// 	if (head->next != NULL)
	// 	{
	// 		head = head->next;
	// 		printf("HERERE\n");
	// 		ft_pipex(head);
	// 	}
	// 	else
	// 		return (0);
	// 	// 	execve(ft_iscmd(head->path), head->argv, 0);
	// 		// runcmd(paths, av, open(av[ac - 1], O_WRONLY | O_CREAT, 0775), i);
	}
	return (0);
}