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
		return (0);
	path = ft_split(getenv("PATH"), ':');
	while (path[i])
	{
		tmp1 = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp1, str);
		free(tmp1);
		if (access(tmp2, X_OK | R_OK | F_OK) == 0)
			return(tmp2);
		i++;
	}
	return (tmp2);
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
                char *path;
				path = ft_iscmd(head->argv[0]);
				printf("PATH = %s\n", path);
                execve(path, head->argv, 0);
                free(path);
            }
			exit(0);
		}
		else
			wait(0);
		head = head->next;
	}
	return (0);
}