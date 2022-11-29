#include "minishell.h"

int ft_prompt(t_data *data)
{
	char *line;

	while (1)
	{
		line = readline(MPROMPT);
		if (!line)
			break;
		if (ft_strlen(line) == 0)
			continue;

		ft_tokenize(data, line);

		//// test

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

		ft_clean(data, 0);
		//// test

		free(line);
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_data data;

	data.cmdlist = 0;
	data.env = env;
	data.tray = 0;
	// ft_sighandle();
	ft_prompt(&data);
	return (0);
}
