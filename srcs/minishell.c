#include "minishell.h"

int ft_test(t_data *data)
{
	t_cmd *head;
	head = data->cmdlist;

	while (head && data->status == 0)
	{
		printf("\n===== node ======\n");
		printf("argv\t:\t");
		int i = 0;
		while (head->argv && head->argv[i])
			printf("[%s] ", head->argv[i++]);
		printf("\n");
		printf("path\t:\t[%s]\n", head->path);
		printf("infile fd\t:\t[%d]\n", head->infile);
		printf("outfile fd\t:\t[%d]\n", head->outfile);
		printf("pipe\t:\t[%d]\n", head->pipe);
		printf("status\t:\t[%d]\n", head->status);
		printf("hd_lmt\t:\t[%s]\n", head->hd_lmt);
		printf("======= end node =======\n");
		head = head->next;
	}
	return (0);
}

static char *getprompt(void)
{
	char *cwd;
	char *prompt;
	char *tmp;

	cwd = malloc(sizeof(char) * 1024);
	getcwd(cwd, 1023);
	// prompt = ft_strnstr(cwd, "minishell", ft_strlen(cwd));
	tmp = ft_strjoin(cwd, "$ \e[;37m \e[0m");
	prompt = ft_strjoin("\e[;32m", tmp);
	free(cwd);
	free(tmp);
	return (prompt);
}

int ft_prompt(t_data *data)
{
	char *prompt;

	while (1)
	{
		data->status = 0;
		prompt = getprompt();
		// dprintf(2, "prompt is (%s)\n", prompt);
		data->line = readline(prompt);
		free(prompt);
		if (!data->line)
			return (-1);
		if (ft_strlen(data->line) == 0)
			continue;
		ft_lexical(data);
		// ft_tokenize(data);
		// ft_test(data);
		ft_execute(data);
		ft_clean(data, 0);
		add_history(data->line);
		// printf("%d\n", g_status);
		free(data->line);
		data->len = 0;
		// dprintf(2, "end of loop\n");
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	// (void)env;
	t_data data;

	data.cmdlist = 0;
	g_status = 0;
	ft_initenv(&data, env);
	data.tray = 0;
	ft_sighandle();
	ft_prompt(&data);
	ft_exit(&data);
}