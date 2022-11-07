#include "minishell.h"

int ft_delimtiter(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	if (c == '<' || c == '>' || c == '|')
		return (2);
	if (c == '\'' || c == '"')
		return (3);
	return (0);
}

int ft_addquote(char *str, int i)
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
	printf("%s [%d]\n", tmp, j);
	free(tmp);
	return (j);
}

int ft_addsword(char *str, int i)
{
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
	int len = ft_strlen(tmp);
	printf("%s [%d]\n", tmp, len);
	free(tmp);
	return (len);
}

int ft_addword(char *str, int start)
{
	int i;
	char *tmp;

	i = 0;
	while (str[start + i])
	{
		if (ft_delimtiter(str[start + i]) == 0)
			i++;
		if (ft_delimtiter(str[start + i]) != 0 || (str[start + i] == 0 && i > 0))
		{
			tmp = ft_substr(str, start, i);
			printf("%s [%d]\n", tmp, (int)ft_strlen(tmp));
			free(tmp);
			return (i);
		}
	}
	return (i);
}

int ft_tokenize(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_delimtiter(str[i]) == 0)
			i += ft_addword(str, i);
		else if (ft_delimtiter(str[i]) == 2)
			i += ft_addsword(str, i);
		else if (ft_delimtiter(str[i]) == 3)
			i += ft_addquote(str, i);
		else
			i++;
	}
	return (0);
}