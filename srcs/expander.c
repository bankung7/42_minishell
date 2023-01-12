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

int	ft_setexpd(t_data *data, t_token *token, int i, t_expd *stc)
{
	int	j;

	j = 1;
	while (token->str[i + j] && (ft_isalnum(token->str[i + j]) == 1
			|| token->str[i + j] == '_'))
		j++;
	if (ft_strncmp("$?", &token->str[i], 2) == 0)
	{
		stc->tmp = ft_strdup("?");
		stc->env = ft_itoa(g_status);
		j++;
	}
	else
	{
		stc->tmp = ft_substr(token->str, i + 1, j - 1);
		stc->env = ft_getenv(data, stc->tmp);
	}
	return (j);
}

static int	ft_getexpand(t_data *data, t_token *token, int i)
{
	int		j;
	int		len;
	t_expd	stc;

	j = ft_setexpd(data, token, i, &stc);
	stc.new = ft_calloc(sizeof(char), ft_strlen(token->str)
			+ (ft_strlen(stc.env) - ft_strlen(stc.tmp)) + 1);
	if (stc.tmp == 0 || stc.new == 0)
		return (ft_freetoken(data, -1));
	ft_memcpy(stc.new, token->str, i);
	ft_memcpy(&stc.new[ft_strlen(stc.new)], stc.env, ft_strlen(stc.env));
	ft_memcpy(&stc.new[ft_strlen(stc.new)], &token->str[i + j],
		ft_strlen(token->str) - (i + j));
	len = ft_strlen(stc.env);
	free(token->str);
	free(stc.tmp);
	free(stc.env);
	token->str = stc.new;
	return (len);
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
