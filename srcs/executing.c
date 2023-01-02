/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:17:07 by pjerddee          #+#    #+#             */
/*   Updated: 2023/01/02 23:46:57 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_makepath(char *path, char *name)
{
	char	*tmp;

	tmp = ft_calloc(sizeof(char), (ft_strlen(path) + ft_strlen(name) + 2));
	if (!tmp)
		return (0);
	ft_memcpy(tmp, path, ft_strlen(path));
	ft_memcpy(&tmp[ft_strlen(tmp)], "/", 1);
	ft_memcpy(&tmp[ft_strlen(tmp)], name, ft_strlen(name));
	return (tmp);
}

char	*ft_iscmd(t_data *data, t_cmd *cmd)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	**path;

	i = 0;
	tmp = ft_getenv(data, "PATH");
	path = ft_split(tmp, ':');
	free(tmp);
	while (path[i])
	{
		tmp2 = ft_makepath(path[i], cmd->path);
		if (access(tmp2, F_OK | X_OK) == 0)
			return (tmp2);
		free(tmp2);
		i++;
	}
	ft_putstr_fd("command not found\n", 2);
	ft_free2((void **)path, -1);
	return (NULL);
}

int	ft_builtin(t_data *data, t_cmd *cmd)
{
	t_cmd	*head;

	head = cmd;
	if (cmd->outfile != 1)
		dup2(cmd->outfile, 1);
	if (ft_strncmp("echo", head->argv[0], 5) == 0)
		return (ft_echo(head));
	else if (ft_strncmp("env", head->argv[0], 4) == 0)
		return (ft_env(data));
	else if (ft_strncmp("pwd", head->argv[0], 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp("cd", head->argv[0], 3) == 0)
		return (ft_cd(data, head));
	else if (ft_strncmp("export", head->argv[0], 7) == 0)
		return (ft_export(data, head));
	else if (ft_strncmp("unset", head->argv[0], 6) == 0)
		return (ft_unset(data, head));
	else if (ft_strncmp("exit", head->argv[0], 5) == 0)
		return (ft_exit(data));
	return (0);
}

int	ft_runetc(t_data *data, t_cmd *cmd)
{
	t_cmd	*head;

	head = cmd;
	if (access(cmd->path, F_OK | X_OK) == 0)
		return (execve(cmd->path, cmd->argv, data->env));
	else if (ft_iscmd(data, head) != NULL)
		return (execve(ft_iscmd(data, head), cmd->argv, data->env));
	else
		exit(127);
	return (0);
}

int	ft_runcmd(t_data *data, t_cmd *head)
{
	int	pid;
	if (ft_builtin(data, head) == 0)
	{
		pid = fork();
		if (pid < 0)
			return (-1);
		if (pid == 0)
			ft_runetc(data, head);
		else
			waitpid(pid, &g_status, 0);
	}
	return (0);
}

int	ft_execute(t_data *data)
{
	t_cmd	*head;

	if (!data->cmdlist)
		return (-1);
	head = data->cmdlist->next;
	while (head)
	{
		if (pipe(head->pfd) == -1)
			printf("Error at pipe\n");
		head = head->next;
	}
	head = data->cmdlist;
	while (head)
	{
		head->pid = fork();
		if (head->pid == 0)
		{
			if (head->pipe == 1)
			{
				close(head->next->pfd[RD]);
				dup2(head->next->pfd[WR], STDOUT_FILENO);
				close(head->next->pfd[WR]);
			}
			if (head != data->cmdlist) // not first cmd
			{
				close(head->pfd[WR]);
				dup2(head->pfd[RD], STDIN_FILENO);
				close(head->pfd[RD]);
			}
			ft_runcmd(data, head);
			// return (0);
			exit(0);
		}
		if (head != data->cmdlist)
		{
			close(head->pfd[WR]);
			close(head->pfd[RD]);
		}
		head = head->next;
	}
	while (wait(NULL) != -1 || errno != ECHILD) ;
	return (0);
}
