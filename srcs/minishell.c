#include "minishell.h"

char	*get_prompt(char *s)
{
		return(ft_strjoin("\033[;32m", ft_strjoin(s,"$ \033[;37m")));
}

int main(void)
{
	char *line;
	char	prompt[100];
	t_mini data;

	data.cmdlist = 0;
	while (1)
	{
		getcwd(prompt, sizeof(prompt));
		line = readline(get_prompt(ft_strnstr(prompt, "minishell", ft_strlen(prompt))));
		if (!line)
			continue;
		ft_tokenize(&data, line);

		// ----- link list
		// int i = 0;
		// t_cmd *head;
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
