#include "minishell.h"

// trim quote
int ft_qtrim(t_data *data, int index)
{
	int i;
	int j;
	int quote;
	char *tmp;

	i = 0;
	j = 0;
	tmp = ft_calloc(sizeof(char), (ft_strlen(data->tray[index]) + 1));
	if (!tmp)
		return (-1);
	while (data->tray[index][i])
	{
		if (ft_isdelimit(data->tray[index], i) == SQUOTE || ft_isdelimit(data->tray[index], i) == DQUOTE)
		{
			quote = ft_isdelimit(data->tray[index], i++);
			while (ft_isdelimit(data->tray[index], i) != quote)
				tmp[j++] = data->tray[index][i++];
			quote = 0;
			i++;
		}
		else
			tmp[j++] = data->tray[index][i++];
	}
	free(data->tray[index]);
	data->tray[index] = ft_strdup(tmp);	
	free(tmp);
	return (0);
}

// except case
// "$VARxxx" => [$VARxxx]
// $VARxxx => [$VARxxx]

int ft_replacevar(t_data *data, int index, char *find, int start)
{
	int flen;
	char *val;
	char *tmp;

	flen = ft_strlen(find) + 1;
	val = ft_getenv(data, find);
	tmp = ft_calloc(sizeof(char), ft_strlen(data->tray[index]) + ft_strlen(val) - flen + 1);

	// printf("ask or space [%d]\n", olen + vlen - flen + 1);
	ft_memcpy(tmp, data->tray[index], start);
	// printf("first %s\n", tmp);
	ft_memcpy(&tmp[ft_strlen(tmp)], val, ft_strlen(val));
	// printf("second %s\n", tmp);
	ft_memcpy(&tmp[ft_strlen(tmp)], &data->tray[index][start + flen], ft_strlen(data->tray[index]) - (start + flen));
	// printf("third %s\n", tmp);
	// printf("tmp : %s\n", tmp);
	free(data->tray[index]);
	data->tray[index] = tmp;
	// free(tmp);
	free(val);
	return (0);
}

int ft_prepvar(t_data *data, int index, char *str, int start)
{
	int i;
	char *tmp;

	i = 1;
	while (str[i])
	{
		if (ft_isdelimit(str, i) == 0 || ft_isdelimit(str, i) >= 11)
			break;
		else
			i++;
	}
	if (i > 1)
	{
		tmp = ft_substr(str, 1, i - 1);
		// printf("find : %s\n", tmp);
		ft_replacevar(data, index, tmp, start);
		free(tmp);
	}
	return (0);
}

int ft_checkex(t_data *data, int index)
{
	int i;
	int quote;
	char *str;

	i = 0;
	quote = 0;
	str = data->tray[index];
	while (str[i])
	{
		if (str[i] == '\'')
			quote = (quote + 1) % 2;
		if (str[i] == '$' && quote == 0)
		{
			if (str[i + 1] == '$')
				return (0);
			ft_prepvar(data, index, &str[i], i);
			str = data->tray[index];
			i--;
			// printf("next : %s\n", &str[i]);
		}
		i++;
	}
	return (0);
}

int ft_expander(t_data *data)
{
	int i;

	i = 0;
	while (data->tray[i])
	{
		if (ft_strchr(data->tray[i], '$') != 0)
			ft_checkex(data, i);
		ft_qtrim(data, i);
		i++;
	}
	return (0);
}