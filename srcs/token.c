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
	if (str[i + j] != 0)
		j++;
	tmp = ft_substr(str, i, j);
	ft_buildlist(data, tmp, WORD);
	// printf("%s [%d]\n", tmp, j);
	free(tmp);
	return (j);
}

int ft_addsword(t_mini *data, char *str, int i)
{
	int len;
	char *tmp;

	if (str[i] == '|' && str[i + 1] == '|')
		tmp = ft_strdup("||");
	else if (str[i] == '|')
		tmp = ft_strdup("|");
	else if (str[i] == '<' && str[i + 1] == '<')
		tmp = ft_strdup("<<");
	else if (str[i] == '<')
		tmp = ft_strdup("<");
	else if (str[i] == '>' && str[i + 1] == '>')
		tmp = ft_strdup(">>");
	else if (str[i] == '>')
		tmp = ft_strdup(">");
	else
		return (1);
	len = ft_strlen(tmp);
	// printf("%s [%d]\n", tmp, len);
	ft_buildlist(data, tmp, ft_delimiter(str, i));
	free(tmp);
	return (len);
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
			ft_buildlist(data, tmp, WORD);
			// printf("%s [%d]\n", tmp, (int)ft_strlen(tmp));
			free(tmp);
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
		else if (type > 0 && type < 10)
			i += ft_addsword(data, str, i);
		else if (type == 10 || type == 11)
			i += ft_addquote(data, str, i);
		else
			i++;
	}
	return (0);
}