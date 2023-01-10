#include "minishell.h"

// test token
int	ft_ttoken(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (data->status == 0)
			printf("%s [%d] ", token->str, token->type);
		token = token->next;
		if (data->token->str)
			free(data->token->str);
		free(data->token);
		data->token = token;
	}
	printf("\n");
	data->token = 0;
	return (0);
}

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
