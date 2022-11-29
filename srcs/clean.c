#include "minishell.h"

int	ft_clean(t_data *data, int res)
{
	int		i;
	t_cmd	*head;

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
