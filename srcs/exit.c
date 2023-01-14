#include "minishell.h"

int	ft_clean(t_data *data, int res)
{
	t_cmd	*head;

	ft_freetoken(data, res);
	if (data->cmdlist == 0)
		return (res);
	head = data->cmdlist;
	while (head)
	{
		ft_freecmd(head, 0);
		head = head->next;
		free(data->cmdlist);
		data->cmdlist = head;
	}
	ft_closefd(data, res);
	data->cmdlist = 0;
	return (res);
}

int	ft_exit(t_data *data, int mode)
{
	int	i;

	if (mode == 1)
		return (0);
	i = 0;
	ft_clean(data, 0);
	while (data->env && data->env[i])
		free(data->env[i++]);
	free(data->env);
	rl_clear_history();
	printf("Bye~\n");
	exit(g_status);
	return (0);
}
