#include "minishell.h"

static void	export_oldpwd(t_data *data)
{
	char	*cwd;
	t_cmd	tmp;

	cwd = malloc(sizeof(char)* 1024);
	getcwd(cwd, 1023);
	tmp.path = ft_strjoin("export OLDPWD=", cwd);
	free(cwd);
	tmp.argv = ft_split(tmp.path, ' ');
	ft_export(data, &tmp);
	free(tmp.path);
	ft_free2((void **)tmp.argv, 0);
}

static char	*getpath(t_data *data, t_cmd *cmd)
{
	char	*old_path;

	if (cmd->argv[1] == NULL || ft_strncmp(cmd->argv[1], "~", 2)  == 0)
		return (ft_getenv(data, "HOME"));
	else if (ft_strncmp(cmd->argv[1], "-", 2)  == 0)
	{
		old_path = ft_getenv(data, "OLDPWD");
		if (old_path == NULL)
			return (NULL);
		printf("%s\n", old_path);
		return (old_path);
	}
	else if (ft_strchr(cmd->argv[1], '~'))
		return (ft_strjoin(ft_getenv(data, "HOME"), ft_strchr(cmd->argv[1], '~') + 1));
	else
		return (cmd->argv[1]);
}

int	ft_cd(t_data *data, t_cmd *cmd)
{
	char	*path;

	path = getpath(data, cmd);
	g_status = 0;
	if (path == NULL)
		printf("OLDPWD not set\n");
	else
	{
		if (access(path, F_OK) != 0)
			printf("No such directory\n");
		else
		{
			export_oldpwd(data);
			chdir(path);
		}
		// free(path);
	}
	g_status = 0;
	return (1);
}
