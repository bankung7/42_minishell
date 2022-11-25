#include "minishell.h"

int ft_isdelimit(char *str, int i)
{
	if (str[i] == ' ' || str[i] == '\t' || str[i] == 0)
		return (DELIMITER);
	if (ft_strncmp("<<", &str[i], 2) == 0)
		return (HEREDOC);
	if (str[i] == '<')
		return (INFILE);
	if (ft_strncmp(">>", &str[i], 2) == 0)
		return (APPEND);
	if (str[i] == '>')
		return (OUTFILE);
	if (str[i] == '|')
		return (PIPE);
	if (str[i] == '\'')
		return (SQUOTE);
	if (str[i] == '"')
		return (DQUOTE);
    if (str[i] == '$')
        return (DOLLARS);
	return (-1);
}

int ft_rebuild(t_data *data, char *str)
{
	int i;
	char **tmp;

	i = 0;
	if (!str)
		return (-1);
	while (data->tray && data->tray[i])
		i++;
	i += 2;
	tmp = malloc(sizeof(char*) * (i));
	if (!tmp)
		return (-1);
	tmp[--i] = 0;
	tmp[--i] = str;
	while (--i >= 0)
		tmp[i] = data->tray[i];
	if (data->tray)
		free(data->tray);
	data->tray = tmp;
	return (0);
}

int ft_buildword(t_data *data, char *str, int i)
{
	int j;
	int quote;
	char *tmp;

	j = 0;
	quote = 0;
	while (str[i + j])
	{
		if ((str[i + j] == '\'' || str[i + j] == '"') && quote == 0)
			quote = ft_isdelimit(str, i + j);
		else if ((str[i + j] == '\'' || str[i + j] == '"') && quote == ft_isdelimit(str, i + j))
			quote = 0;
		if (((ft_isdelimit(str, i + j) >= 0 && ft_isdelimit(str, i + j) <= 5) 
            || str[i + j + 1] == 0) && quote == 0)
		{
			if (ft_isdelimit(str, i + j) != 0 && str[i + j + 1] == 0)
				j++;
			tmp = ft_substr(str, i , j);
			if (ft_rebuild(data, tmp) == -1)
				return (ft_strlen(str));
			return (j);
		}
		else
			j++;
	}
	return (ft_strlen(str));
}

int ft_buildschar(t_data *data, char *str, int type)
{
	char *tmp;

	tmp = 0;
	if (type == INFILE)
		tmp = ft_strdup("<");
	else if (type == HEREDOC)
		tmp = ft_strdup("<<");
	else if (type == OUTFILE)
		tmp = ft_strdup(">");
	else if (type == APPEND)
		tmp = ft_strdup(">>");
	else if (type == PIPE)
		tmp = ft_strdup("|");
	if (ft_rebuild(data, tmp) == -1)
		return (ft_strlen(str));
	return (ft_strlen(tmp));
}

int ft_tokenize(t_data *data, char *str)
{
	int	i;
	int	c;

	i = 0;
	while (str[i])
	{
		c = ft_isdelimit(str, i);
		if (c == -1 || (c >= SQUOTE && c <= DOLLARS))
			i += ft_buildword(data, str, i);
		else if (c >= 1 && c <= 5)
			i += ft_buildschar(data, str, c);
		else
			i++;
	}
	return (0);
}