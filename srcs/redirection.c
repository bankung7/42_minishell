#include "minishell.h"

int	ft_redirection(t_data *data, char *file)
{
	t_cmd	*head;

	head = data->cmdlist;
	while (head->next)
		head = head->next;
	if (head->status == INFILE)
		head->infile = open(file, O_RDONLY);
	else if (head->status == OUTFILE)
		head->outfile = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (head->status == APPEND)
		head->outfile = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	//Is these part needed??
	// if (head->infile < 0 || head->outfile < 0)
	// 	return (-1);
	head->status = 0;
	free(file);
	return (0);
}
