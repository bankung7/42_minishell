#include "minishell.h"

int ft_clean(t_data *data, int res)
{
	int i;
	t_cmd *head;

	head = data->cmdlist;
	while (head)
	{
		i = 0;
		while (head->argv && head->argv[i])
			free(head->argv[i++]);
		free(head->path);
		free(head->argv);
		if (head->infile > 2)
			close(head->infile);
		if (head->outfile > 2)
			close(head->outfile);
		head = head->next;
		free(data->cmdlist);
		data->cmdlist = head;
	}
	data->cmdlist = 0;
	return (res);
}

int ft_exit(t_data *data)
{
	int i;

	i = 0;
	ft_clean(data, 0);
	while (data->env && data->env[i])
		free(data->env[i++]);
	free(data->env);
	rl_clear_history();
	printf("Bye~\n");
	exit(0);
	return (0);
}