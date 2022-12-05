#include "minishell.h"

int ft_execve(t_data *data, t_cmd *cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
	{
		execve(cmd->path, cmd->argv, data->env);
		exit(0);
	}
	else
		waitpid(pid, 0, 0);
	return (0);
}

int ft_iscmd(t_data *data, t_cmd *cmd)
{
	int i;
	char *tmp;
	char *tmp2;
	char **path;

	i = 0;
	tmp = ft_getenv(data, "PATH");
	path = ft_split(tmp, ':');
	free(tmp);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		tmp2 = ft_strjoin(tmp, cmd->path);
		free(tmp);
		if (access(tmp2, F_OK | X_OK) == 0)
		{
			free(cmd->path);
			cmd->path = tmp2;
			ft_execve(data, cmd);
			ft_free2((void **)path, 0);
			return (0);
		}
		free(tmp2);
		i++;
	}
	printf("no command\n");
	return (ft_free2((void **)path, -1));
}

int ft_execute(t_data *data)
{
	t_cmd *head;

	if (!data->cmdlist)
		return (-1);
	head = data->cmdlist;
	while (head)
	{
		// printf("command : %s => pipe %d\n", head->path, head->pipe);
		// if (ft_strncmp("echo", head->argv[0], 5) == 0)
		// 	ft_echo(head);
		// else if (ft_strncmp("env", head->argv[0], 4) == 0)
		// 	ft_env(data);
		// else if (ft_strncmp("pwd", head->argv[0], 4) == 0)
		// 	ft_pwd();
		// else if (ft_strncmp("cd", head->argv[0], 3) == 0)
		// 	continue;
		// else if (ft_strncmp("export", head->argv[0], 7) == 0)
		// 	ft_export(data, head);
		// else if (ft_strncmp("unset", head->argv[0], 6) == 0)
		// 	ft_unset(data, head);
		// else if (ft_strncmp("exit", head->argv[0], 5) == 0)
		// 	ft_exit(data);
		// else if (ft_iscmd(data, head) == -1)
		// 	return (-1);
		int count = 0;
		t_cmd *chead;
		chead = data->cmdlist;
		while (chead->pipe == 1 && count++ >= 0)
			chead = chead->next;
		if (head->pipe == 1)
		{
			ft_pipex(data, head);
			while (count-- > 0)
			{
				head = head->next;
				ft_clean1(data, 0);
				data->cmdlist = head;
			}
		}
		else
			if (ft_iscmd(data, head) == -1)
				return (-1);
		head = head->next;
		if (head)
			printf("next : %s\n", head->path);
		ft_clean1(data, 0);
	}
	return (0);
}
