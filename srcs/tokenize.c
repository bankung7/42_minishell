#include "minishell.h"

int	ft_isdelimit(char *str, int i)
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

int	ft_rebuild(t_data *data, char *str)
{
	int		i;
	char	**tmp;

	i = 0;
	if (!str)
		return (-1);
	while (data->tray && data->tray[i])
		i++;
	i += 2;
	tmp = malloc(sizeof(char *) * (i));
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

int	ft_buildword(t_data *data, char *str, int i)
{
	int		j;
	int		quote;
	char	*tmp;

	j = 0;
	quote = 0;
	tmp = 0;
	while (str[i + j])
	{
		if ((str[i + j] == '\'' || str[i + j] == '"') && quote == 0)
			quote = ft_isdelimit(str, i + j);
		else if ((str[i + j] == '\'' || str[i + j] == '"') && quote == ft_isdelimit(str, i + j))
			quote = 0;
		if (((ft_isdelimit(str, i + j) >= 0 && ft_isdelimit(str, i + j) <= 5) || str[i + j + 1] == 0) && quote == 0)
		{
			if (ft_isdelimit(str, i + j) != 0 && str[i + j + 1] == 0)
				j++;
			tmp = ft_expander(data, str, i, j);
			ft_buildnode(data, tmp, WORD);
			return (j);
		}
		else
			j++;
	}
	return (ft_strlen(str));
}

int	ft_buildschar(t_data *data, char *str, int type)
{
	t_cmd	*head;

	if (!data->cmdlist)
		data->cmdlist = ft_newnode();
	head = data->cmdlist;
	while (head->next)
		head = head->next;
	if (head->status != 0 && head->status != WORD)
	{
		printf("deal error here [%d]\n", head->status);
		return (-ft_strlen(str));
	}
	if (type == INFILE)
		head->status = type;
	else if (type == OUTFILE || type == APPEND)
		head->status = type;
	else if (type == PIPE)
		return (ft_bpipe(data, str));
	return (((type + 1) % 2) + 1);
}

int	ft_tokenize(t_data *data, char *str)
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
		if (i < 0)
		{
			printf("some error\n");
			return (ft_clean(data, 1));
		}
	}
	return (0);
}
