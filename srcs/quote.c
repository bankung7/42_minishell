#include "minishell.h"

int	ft_unquote(t_token *token, int i, int quote)
{
	int	j;

	j = 0;
	ft_memmove(&token->str[i], &token->str[i + 1],
		ft_strlen(token->str) - i);
	while (token->str[i + j] && token->str[i + j] != quote)
		j++;
	if (token->str[i + j] == 0)
		token->str[i] = 0;
	else
		ft_memmove(&token->str[i + j], &token->str[i + j + 1],
			ft_strlen(token->str) - (i + j));
	return (j - 2);
}

int	ft_dquote(t_data *data, t_token *token, int i)
{
	int	j;

	j = 1;
	if (token->str[i + j] == '"')
		return (ft_unquote(token, i, '"') + 2);
	while (data->status == 0 && token->str[i + j])
	{
		if (token->str[i + j] == '"')
			break ;
		if (token->str[i + j] == '$')
			j += ft_getexpand(data, token, i + j);
		else
			j++;
	}
	j = ft_unquote(token, i, '"') + 2;
	return (j);
}
