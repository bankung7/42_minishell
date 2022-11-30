#include "minishell.h"

int ft_execute(t_data *data)
{
	t_cmd *head;

	if (!data->cmdlist)
		return (-1);
	head = data->cmdlist;
	while (head)
	{
		if (ft_strncmp("echo", head->argv[0], 5) == 0)
			ft_echo(head);
		else if (ft_strncmp("env", head->argv[0], 4) == 0)
			ft_env(data);
		head = head->next;
	}
	return (0);
}