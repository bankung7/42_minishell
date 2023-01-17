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
		{
			ft_free2((void **)path, 0);
			return (tmp2);
		}
		free(tmp2);
		i++;
	}
	ft_putstr_fd(cmd->path, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_status = 126;
	ft_free2((void **)path, -1);
	return (NULL);
}

int	ft_builtin(t_data *data, t_cmd *cmd)
{
	if (cmd->outfile != 1)
		dup2(cmd->outfile, 1);
	if (cmd->path == 0)
		return (0);
	if (ft_strncmp("echo", cmd->argv[0], 5) == 0)
		exit(ft_echo(cmd));
	if (ft_strncmp("env", cmd->argv[0], 4) == 0)
		exit(ft_env(data));
	if (ft_strncmp("pwd", cmd->argv[0], 4) == 0)
		exit(ft_pwd());
	if (ft_strncmp("cd", cmd->argv[0], 3) == 0)
		return (1);
	if (ft_strncmp("export", cmd->argv[0], 7) == 0)
		return (1);
	if (ft_strncmp("unset", cmd->argv[0], 6) == 0)
		return (1);
	if (ft_strncmp("exit", cmd->argv[0], 5) == 0)
		return (1);
	return (0);
}

// mode = 1(not runcmd)
int	ft_builtin_out(t_data *data, t_cmd *cmd, int mode)
{
	if (cmd->outfile != 1)
		dup2(cmd->outfile, 1);
	if (ft_strncmp("cd", cmd->argv[0], 3) == 0)
		return (ft_cd(data, cmd, mode));
	if (ft_strncmp("export", cmd->argv[0], 7) == 0)
		return (ft_export(data, cmd, mode));
	if (ft_strncmp("unset", cmd->argv[0], 6) == 0)
		return (ft_unset(data, cmd, mode));
	else if (ft_strncmp("exit", cmd->argv[0], 5) == 0)
		return (ft_exit(data, mode));
	return (1);
}

// test case error status only for the last pipe
int	ft_runcmd(t_data *data, t_cmd *cmd)
{
	char	*path;

	if (cmd->path != 0 && access(cmd->path, F_OK | X_OK) == 0)
		return (execve(cmd->path, cmd->argv, data->env));
	if (cmd->path == 0)
	{
		printf("exit 126\n");
		exit(126);
	}
	path = ft_iscmd(data, cmd);
	if (path != NULL)
	{
		free(cmd->path);
		cmd->path = path;
		return (execve(cmd->path, cmd->argv, data->env));
	}
	else
	{
		free(path);
		exit(127);
	}
	return (0);
}
