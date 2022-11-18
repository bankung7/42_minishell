#include "minishell.h"

void	ft_freesplit(char **str);

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
	int		fd[2];
	pid_t	pid;
	t_cmd	*head;

	if (!data->cmdlist)
		return (-1);
	if (pipe(fd) < 0)
	{
		ft_putstr_fd("Error at pipe.", 2);
		return (-1);
	}
	head = data->cmdlist;
	if (head->infile != 0)
		dup2(head->infile, 0);
	while (head)
	{
		if (head != data->cmdlist)
			dup2(fd[0], 0);
		pid = fork();
		if (pid == -1)
			return (-1);
		else if (pid == 0)
		{
            close(fd[0]);
			if (head->next != NULL)
				dup2(fd[1], 1);
			// else
			// {
			// 	dup2(head->outfile, 1);
			// 	close(head->outfile);
			// }
			close(fd[1]);
			if (head->type == BUILTIN)
                ft_isbuiltin(head, 1);
            else
            {
                char	*bin_path = ft_iscmd(head->path);
				execve(bin_path, head->argv, 0);
                free(bin_path);
            }
		}
		// else
		// {
		// 	wait(NULL);
		// 	close(fd[1]);
		// 	dup2(fd[0], 0);
		// 	close(fd[0]);
		// }
		head = head->next;
	}
	return (0);
}

void	ft_freesplit(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}