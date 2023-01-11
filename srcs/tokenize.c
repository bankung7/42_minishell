#include "minishell.h"

int	ft_addtoken(t_data *data, char *str, int type)
{
	t_token	*node;
	t_token	*head;

	node = malloc(sizeof(t_token));
	if (!node)
		return (-1);
	node->str = str;
	node->type = type;
	node->len = 0;
	node->tmp = 0;
	node->env = 0;
	node->new = 0;
	node->next = 0;
	if (data->token == 0)
		data->token = node;
	else
	{
		head = data->token;
		while (head->next)
			head = head->next;
		head->next = node;
	}
	return (0);
}
