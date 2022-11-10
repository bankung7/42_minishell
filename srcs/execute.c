#include "minishell.h"

int ft_checkcmd(t_mini *data)
{
	t_cmd *head;

	head = data->cmdlist;
	if (!head)
		return (-1);
	while (head)
	{
        if (ft_isbuiltin(head, 0) == 0)
            head->type = BUILTIN;
        else if (ft_iscmd(head->path) == 0)
            head->type = COMMAND;
		head = head->next;
	}
	return (0);
}

int ft_iscmd(char *str)
{
    int status;
	char *tmp;

    status = 0;
    tmp = ft_strjoin("/bin/", str);
    status = access(tmp, F_OK);
    free(tmp);
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
                char *path;
                path = ft_strjoin("/bin/", head->path);
                execve(path, head->vector, 0);
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