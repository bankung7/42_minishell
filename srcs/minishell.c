#include "minishell.h"

int	ft_test(t_data *data)
{
	t_cmd	*head;
	int		i;

	head = data->cmdlist;
	while (head)
	{
		printf("\n===== node ======\n");
		printf("argv\t:\t");
		i = 0;
		while (head->argv && head->argv[i])
			printf("[%s] ", head->argv[i++]);
		printf("\n");
		printf("path\t:\t[%s]\n", head->path);
		printf("infile fd\t:\t[%d]\n", head->infile);
		printf("outfile fd\t:\t[%d]\n", head->outfile);
		printf("pipe\t:\t[%d]\n", head->pipe);
		printf("status\t:\t[%d]\n", head->status);
		printf("heredeoc limiter\t:\t[%s]\n", head->hd_lmt);
		printf("======= end node =======\n");
		head = head->next;
	}
	return (0);
}

static char	*getprompt(void)
{
	char	*cwd;
	char	*prompt;
	char	*tmp;

	cwd = malloc(sizeof(char) * 1024);
	getcwd(cwd, 1023);
	tmp = ft_strjoin(cwd, "$ \e[;37m \e[0m");
	prompt = ft_strjoin("\e[;32m", tmp);
	free(cwd);
	free(tmp);
	return (prompt);
}

int	ft_prompt(t_data *data)
{
	char	*prompt;

	while (1)
	{
        data->cmdlist = 0;
        data->line = 0;
        data->len = 0;
        data->status = 0;
        data->token = 0;
		data->ori_fd[RD] = dup(STDIN_FILENO);
		data->ori_fd[WR] = dup(STDOUT_FILENO);
		prompt = getprompt();
		data->line = readline(prompt);
		free(prompt);
		if (!data->line)
			return (-1);
		if (ft_strlen(data->line) == 0)
			continue ;
		if (ft_lexical(data) == 0 && ft_parser(data) == 0)
        {
            // ft_test(data);
		    ft_execute(data);
        }
		ft_clean(data, 0);
		add_history(data->line);
		free(data->line);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.cmdlist = 0;
	g_status = 0;
	ft_initenv(&data, env);
	data.tray = 0;
	ft_sighandle();
	ft_prompt(&data);
	ft_exit(&data);
}
