#include "minishell.h"

int	ft_unquote(t_token *token, int i, int quote)
{
	int	j;

	j = 1;
	ft_memmove(&token->str[i], &token->str[i + j],
		ft_strlen(token->str) - (i + j) + 1);
	if (token->str[i] == quote)
	{
		ft_memmove(&token->str[i], &token->str[i + j],
			ft_strlen(token->str) - (i + j) + 1);
		return (0);
	}
	while (token->str[i + j] && token->str[i + j] != quote)
		j++;
	if (token->str[i + j] == 0)
		token->str[i] = 0;
	else
		ft_memmove(&token->str[i + j], &token->str[i + j + 1],
			ft_strlen(token->str) - (i + j));
	return (j);
}

int	ft_dquote(t_data *data, t_token *token, int i)
{
	int	j;

	j = 1;
	while (data->status == 0 && token->str[i + j]
		&& token->str[i + j] != '"')
	{
		if (token->str[i + j] == '$')
			j += ft_getexpand(data, token, i + j);
		j++;
	}
	ft_unquote(token, i, '"');
	return (j - 2);
}
