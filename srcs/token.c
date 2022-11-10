#include "minishell.h"

int ft_delimiter(char *str, int i)
{
	if (str[i] == ' ' || str[i] == '\t')
		return (0);
	else if (str[i] == '|' && str[i + 1] == '|')
		return (OR);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '<')
		return (INFILE);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '>')
		return (OUTFILE);
	else if (str[i] == '\'')
		return (SQUOTE);
	else if (str[i] == '"')
		return (DQUOTE);
	return (-1);
}

int ft_addquote(t_mini *data, char *str, int i)
{
	int j;
	char c;
	char *tmp;

	j = 1;
	c = str[i];
	while (str[i + j] && str[i + j] != c)
		j++;
	if (str[i + j] == c)
		j++;
	else if (str[i + j] == 0 || j == 1)
		return (ft_clearlist(data, ft_strlen(str)));
	tmp = ft_substr(str, i + 1, j - 2);
	if (ft_buildword(data, tmp) == -1)
		return (ft_clearlist(data, ft_strlen(str)));
	return (j);
}

int ft_addword(t_mini *data, char *str, int start)
{
	int i;
	char *tmp;

	i = 0;
	while (str[start + i])
	{
		if (ft_delimiter(str, start + i) == -1)
			i++;
		if (ft_delimiter(str, start + i) != -1 || (str[start + i] == 0 && i > 0))
		{
			tmp = ft_substr(str, start, i);
			if (ft_buildword(data, tmp) == -1)
				return (ft_clearlist(data, ft_strlen(str)));
			return (i);
		}
	}
	return (i);
}

int ft_tokenize(t_mini *data, char *str)
{
	int i;
	int type;

	i = 0;
	while (str[i])
	{
		type = ft_delimiter(str, i);
		if (type == -1)
			i += ft_addword(data, str, i);
		else if (type == PIPE)
			i += ft_buildpipe(data, str);
		else if (type >= 3 && type <= 6)
			i += ft_buildfd(data, str, type);
		else if (type == SQUOTE || type == DQUOTE)
			i += ft_addquote(data, str, i);
		else
			i++;
	}
	return (0);
}