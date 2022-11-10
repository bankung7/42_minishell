#include "minishell.h"

int main(void)
{
	char *line;
	t_mini *data;

	data = malloc(sizeof(t_mini));
	if (!data)
		return (-1);
	data->cmdlist = 0;
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			continue;
		ft_tokenize(data, line);
		free(line);

		// ----- link list
		t_cmd *head;
		int i = 0;
		head = data->cmdlist;
		while (head)
		{
			printf("\n========== node [%d] =========\n", i);
			printf("vector\t:\t");
			int j = 0;
			while (head && head->vector[j])
				printf("%s ;", head->vector[j++]);
			printf("\n");
			printf("Command\t:\t[%s]\n", head->cmd);
			printf("Path\t:\t[%s]\n", head->path);
			printf("Infile\t:\t[%d]\n", head->infile);
			printf("Outfile\t:\t[%d]\n", head->outfile);
			printf("Type\t:\t[%d]\n", head->type);
			printf("==============================\n");
			head = head->next;
			i++;
		}
		if (ft_checkcmd(data) == -1)
			printf("syntax error\n");
		else
			ft_runcmd(data);
		ft_clearlist(data, 0);
		// ===== link list
		printf("\n");
	}
	free(data);
	return (0);
}