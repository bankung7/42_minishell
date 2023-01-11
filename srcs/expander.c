#include "minishell.h"

static int	ft_unquote(t_token *token, int i, int quote)
{
	int	j;

	j = 1;
	ft_memmove(&token->str[i], &token->str[i + j],
		ft_strlen(token->str) - (i + j) + 1);
	while (token->str[i + j] && token->str[i + j] != quote)
		j++;
	if (token->str[i + j] == 0)
		token->str[i] = 0;
	else
		ft_memmove(&token->str[i + j], &token->str[i + j + 1],
			ft_strlen(token->str) - (i + j));
	return (j);
}

int	ft_envlen(char *tmp, char *env)
{
	int	len;

	len = ft_strlen(env);
	free(tmp);
	free(env);
	return (len);
}

static int	ft_getexpand(t_data *data, t_token *token, int i)
{
	int		j;
	char	*tmp;
	char	*env;
	char	*new;

	j = 1;
	while (token->str[i + j] && (ft_isalnum(token->str[i + j]) == 1
			|| token->str[i + j] == '_'))
		j++;
	tmp = ft_substr(token->str, i + 1, j - 1);
	env = ft_getenv(data, tmp);
	new = ft_calloc(sizeof(char), ft_strlen(token->str)
			+ (ft_strlen(env) - ft_strlen(tmp)) + 1);
	if (tmp == 0 || new == 0)
		return (ft_freetoken(data, -1));
	ft_memcpy(new, token->str, i);
	ft_memcpy(&new[ft_strlen(new)], env, ft_strlen(env));
	ft_memcpy(&new[ft_strlen(new)], &token->str[i + j],
		ft_strlen(token->str) - (i + j));
	free(token->str);
	token->str = new;
	return (ft_envlen(tmp, env));
}

static int	ft_dquote(t_data *data, t_token *token, int i)
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
	return (j - 1);
}

int	ft_expander(t_data *data, t_token *token)
{
	int		i;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'')
			i += ft_unquote(token, i, '\'');
		else if (token->str[i] == '"')
			i += ft_dquote(data, token, i);
		else if (token->str[i] == '$')
			i += ft_getexpand(data, token, i);
		else
			i++;
	}
	return (0);
}
