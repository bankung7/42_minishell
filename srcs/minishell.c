#include "minishell.h"

int main(void)
{
	char *line;
	t_mini data;

	data.cmdlist = 0;
	ft_sighandle();
	while (1)
	{
		char *path = getenv("PATH");
		printf("%s\n", path);
		line = readline(PROMPT);
		if (!line)
		{
			printf("Exit Bye~\n");
			break ;
		}
		ft_tokenize(&data, line);

		// ----- link list
		// t_cmd *head;
		// int i = 0;
		// head = data.cmdlist;
		// while (head)
		// {
		// 	printf("\n========== node [%d] =========\n", i);
		// 	printf("cmd\t:\t");
		// 	int j = 0;
		// 	while (head && head->argv[j])
		// 		printf("%s ;", head->argv[j++]);
		// 	printf("\n");
		// 	printf("Path\t:\t[%s]\n", head->path);
		// 	printf("Infile\t:\t[%d]\n", head->infile);
		// 	printf("Outfile\t:\t[%d]\n", head->outfile);
		// 	printf("Type\t:\t[%d]\n", head->type);
		// 	printf("==============================\n");
		// 	head = head->next;
		// 	i++;
		// }

		if (ft_checkcmd(&data) == -1)
			printf("syntax error\n");
		else
			ft_runcmd(&data);
		ft_clearlist(&data, 0);
		// ===== link list
		// printf("\n");
	}
	return (0);
}
