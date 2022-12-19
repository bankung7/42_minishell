/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 22:17:07 by pjerddee          #+#    #+#             */
/*   Updated: 2022/12/19 14:57:51 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execve(t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (-1);
	else if (pid == 0)
		execve(cmd->path, cmd->argv, data->env);
	else
		waitpid(pid, 0, 0);
	return (0);
}

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

int	ft_iscmd(t_data *data, t_cmd *cmd)
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
	ft_putstr_fd("command not found\n", 2);
	return (ft_free2((void **)path, -1));
}

int	ft_runcmd(t_data *data, t_cmd *cmd)
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
	else if (ft_iscmd(data, head) == -1)
		return (-1);
	return (0);
}

int	ft_execute(t_data *data)
{
	t_cmd *head;
	int	in;
	int	out;

	if (!data->cmdlist)
		return (-1);
	head = data->cmdlist;
	while (head)
	{
		if (head->pipe == 1)
		{
			if (ft_topipe(data, head) == -1)
				return (-1);
			break ;
		}
		in = dup(0);
		out = dup(1);
		dup2(head->infile, 0);
		dup2(head->outfile, 1);
		if (ft_runcmd(data, head) == -1)
			return (0);
		close(head->infile);
		close(head->outfile);
		head = head->next;
		ft_clean1(data, 0);
	}
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
	return (0);
}
