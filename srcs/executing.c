#include "minishell.h"

int ft_execve(t_data *data, t_cmd *cmd)
{
	pid_t pid;
	char *path;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		path = ft_strjoin("/bin/", cmd->path);
		if (access(path, F_OK) != 0)
		{
			perror("execve error\n");
			return (-1);
		}
		printf("%s\n", path);
		execve(path, cmd->argv, data->env);
		exit(0);
	}
	else
		waitpid(pid, 0, 0);
	return (0);
}

int ft_execute(t_data *data)
{
	t_cmd *head;

	if (!data->cmdlist)
		return (-1);
	head = data->cmdlist;
	while (head)
	{
		if (ft_strncmp("echo", head->argv[0], 5) == 0)
			ft_echo(head);
		else if (ft_strncmp("env", head->argv[0], 4) == 0)
			ft_env(data);
		else if (ft_strncmp("pwd", head->argv[0], 4) == 0)
			ft_pwd();
		else if (ft_strncmp("export", head->argv[0], 7) == 0)
			ft_export(data, head);
		else if (ft_strncmp("unset", head->argv[0], 6) == 0)
			ft_unset(data, head);
		else if (ft_strncmp("exit", head->argv[0], 5) == 0)
			ft_exit(data);
		else
			if (ft_execve(data, head) == -1)
				return (-1);
		head = head->next;
	}
	return (0);
}