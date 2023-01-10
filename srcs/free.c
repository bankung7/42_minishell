#include "minishell.h"

int	ft_freetoken(t_data *data, int res)
{
	t_token	*token;

	token = data->token;
	if (token == 0)
		return (0);
	while (token)
	{
		if (token->str)
			free(token->str);
		if (token->tmp)
			free(token->tmp);
		if (token->env)
			free(token->env);
		if (token->new)
			free(token->new);
		token = token->next;
	}
	data->status = res;
	return (res);
}