#include "minishell.h"

int	ft_ctype(t_data *data)
{
	if (ft_strncmp(&data->line[data->len], ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(&data->line[data->len], "<<", 2) == 0)
		return (HEREDOC);
	if (data->line[data->len] == '>')
		return (OUTFILE);
	if (data->line[data->len] == '<')
		return (INFILE);
	if (data->line[data->len] == '|')
		return (PIPE);
	if (data->line[data->len] == ' ' || data->line[data->len] == '\t'
		|| data->line[data->len] == '\n')
		return (DELIMITER);
	if (data->line[data->len] == '\'')
		return (SQUOTE);
	if (data->line[data->len] == '"')
		return (DQUOTE);
	return (100);
}

int	ft_cquote(t_data *data, int type)
{
	int	i;

	data->len++;
	while (data->line[data->len])
	{
		i = ft_ctype(data);
		if (i == type)
			break ;
		data->len++;
	}
	if (data->line[data->len] == 0 && (i != type))
		data->status = -1;
	return (0);
}

int	ft_wlexical(t_data *data)
{
	int	i;
	int	type;

	i = data->len;
	while (data->status == 0 && data->line[data->len])
	{
		type = ft_ctype(data);
		if (type == 11 || type == 12)
			ft_cquote(data, type);
		else if (type <= 5)
			break ;
		data->len++;
	}
	if (data->status == 0)
		data->status = ft_addtoken(data,
				ft_substr(data->line, i, data->len - i), WORD);
	return (data->status);
}

// get schar to token
int	ft_slexical(t_data *data, int type)
{
	int	len;

	len = ((type + 1) % 2) + 1;
	data->status = ft_addtoken(data,
			ft_substr(data->line, data->len, len), type);
	data->len += len;
	return (data->status);
}

// check each char and send to tokenize
int	ft_lexical(t_data *data)
{
	int	type;

	while (data->line[data->len] && data->status == 0)
	{
		type = ft_ctype(data);
		if (type >= 11)
			ft_wlexical(data);
		else if (type >= 1)
			ft_slexical(data, type);
		else
			data->len++;
	}
	if (data->status != 0)
		printf("lexical error\n");
	return (0);
}
