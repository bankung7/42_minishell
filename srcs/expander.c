#include "minishell.h"

static char	*ft_qtrim(char *str)
{
	int		i;
	int		j;
	int		quote;
	char	*tmp;

	i = 0;
	j = 0;
	quote = 0;
	tmp = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!tmp)
		return (0);
	while (str[i])
	{
		if (ft_isdelimit(str, i) == SQUOTE || ft_isdelimit(str, i) == DQUOTE)
		{
			quote = ft_isdelimit(str, i++);
			while (ft_isdelimit(str, i) != quote)
				tmp[j++] = str[i++];
			quote = 0;
			i++;
		}
		else
			tmp[j++] = str[i++];
	}
	return (tmp);
}

static char	*ft_replacevar(t_data *data, char *str, char *find, int start)
{
	int		flen;
	char	*val;
	char	*tmp;

	flen = ft_strlen(find) + 1;
	val = ft_getenv(data, find);
	tmp = ft_calloc(sizeof(char), ft_strlen(str) + ft_strlen(val) - flen + 1);
	ft_memcpy(tmp, str, start);
	ft_memcpy(&tmp[ft_strlen(tmp)], val, ft_strlen(val));
	ft_memcpy(&tmp[ft_strlen(tmp)], &str[start + flen],
		ft_strlen(str) - (start - flen));
	if (val)
		free(val);
	return (tmp);
}

static char	*ft_prepvar(t_data *data, char *str, int start)
{
	int		i;
	char	*tmp;
	char	*substr;

	i = 1;
	while (str[start + i])
	{
		if (ft_isdelimit(str, start + i) == 0
			|| ft_isdelimit(str, start + i) >= 11)
			break ;
		else
			i++;
	}
	substr = ft_substr(str, start + 1, i - 1);
	tmp = ft_replacevar(data, str, substr, start);
	free(substr);
	free(str);
	return (tmp);
}

static char	*ft_exword(t_data *data, char *str, int i)
{
	char	*tmp;

	tmp = ft_prepvar(data, str, i);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

char	*ft_expander(t_data *data, char *str, int start, int j)
{
	int		i;
	int		quote;
	char	*tmp;
	char	*word;

	i = 0;
	quote = 0;
	word = ft_substr(str, start, j);
	tmp = 0;
	if (ft_strchr(word, '$') != 0)
	{
		while (word[i])
		{
			if (word[i] == '\'')
				quote = (quote + 1) % 2;
			if (word[i] == '$' && quote == 0)
				word = ft_exword(data, word, i);
			i++;
		}
	}
	tmp = ft_qtrim(word);
	free(word);
	return (tmp);
}
