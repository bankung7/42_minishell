#include "minishell.h"

int ft_iscmd(char *str)
{
	char *tmp;

	// not built-in
	if (ft_isbuiltin(str) == 0)
	{
		tmp = ft_strjoin("/bin/", str);
		if (access(tmp, F_OK) != -1)
		{
			printf("this is a shell command\n");
			return (0);
		}
		else
			return (-1);
	}
	return (0);
}

int ft_checkcmd(t_mini *data)
{
	t_cmd *head;

	head = data->cmdlist;
	if (!head)
		return (-1);
	while (head)
	{
		if (ft_iscmd(head->path) == -1)
			return (-1);
		head = head->next;
	}
	return (0);
}

int ft_isbuiltin(char *str)
{
	int len;

	len = ft_strlen(str);
	if (len == 2 && ft_strncmp("cd", str, 2) == 0)
		return (printf("builtin cd\n"));
	else if (len == 3 && ft_strncmp("pwd", str, 3) == 0)
		return (printf("builtin pwd\n"));
	else if (len == 3 && ft_strncmp("env", str, 3) == 0)
		return (printf("builtin env\n"));
	else if (len == 4 && ft_strncmp("echo", str, 4) == 0)
		return (printf("builtin echo\n"));
	else if (len == 4 && ft_strncmp("exit", str, 4) == 0)
		return (printf("builtin exit\n"));
	else if (len == 5 && ft_strncmp("unset", str, 5) == 0)
		return (printf("builtin unset\n"));
	else if (len == 6 && ft_strncmp("export", str, 6) == 0)
		return (printf("builtin export\n"));
	return (0);
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
			char *path;
			path = ft_strjoin("/bin/", head->path);
			execve(path, head->vector, 0);
			free(path);
			exit(0);
		}
		else
			wait(0);
		head = head->next;
	}
	return (0);
}