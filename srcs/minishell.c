#include "minishell.h"

int ft_test(t_data *data)
{
	t_cmd *head;
	head = data->cmdlist;

	while (head)
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
		printf("status\t:\t[%d]\n", head->status);
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

	cwd = malloc(sizeof(char)* 1024);
	getcwd(cwd, 1023);
	// prompt = ft_strnstr(cwd, "minishell", ft_strlen(cwd));
	tmp = ft_strjoin(cwd,"$ \033[;37m");
	prompt = ft_strjoin("\033[;32m", tmp);
	free(cwd);
	free(tmp);
	return(prompt);
}

int ft_prompt(t_data *data)
{
	char *line;
	char	*prompt;

	while (1)
	{
		prompt = getprompt();
		line = readline(prompt);
		// line = readline(MPROMPT);
		free(prompt);
		if (!line)
			return (-1);
		if (ft_strlen(line) == 0)
			continue ;
		ft_tokenize(data, line);
		ft_test(data);
		ft_execute(data);
		ft_clean(data, 0);
		add_history(line);
		free(line);
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
	ft_initenv(&data, env);
	data.tray = 0;
	ft_sighandle();
	ft_prompt(&data);
	ft_exit(&data);
	return (0);
}
