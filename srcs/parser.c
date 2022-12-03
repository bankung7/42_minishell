#include "minishell.h"

t_cmd	*ft_newnode(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->argv = 0;
	node->path = 0;
	node->infile = 0;
	node->outfile = 1;
	node->status = 0;
	node->next = 0;
	return (node);
}

int	ft_arebuild(t_data *data, char *str)
{
	int		i;
	char	**tmp;
	t_cmd	*head;

	i = 0;
	head = data->cmdlist;
	while (head->next)
		head = head->next;
	while (head->argv && head->argv[i])
		i++;
	i += 2;
	tmp = malloc(sizeof(char *) * i);
	if (!tmp)
		return (-1);
	tmp[--i] = 0;
	tmp[--i] = str;
	while (--i >= 0)
		tmp[i] = head->argv[i];
	if (head->argv)
		free(head->argv);
	head->argv = tmp;
	return (0);
}

int	ft_bword(t_data *data, char *str)
{
	t_cmd	*head;

	if (data->cmdlist == 0)
		data->cmdlist = ft_newnode();
	head = data->cmdlist;
	while (head->next)
		head = head->next;
	if (head->path == 0)
		head->path = ft_strdup(str);
	ft_arebuild(data, str);
	return (0);
}

// deal with double pipe
int	ft_bpipe(t_data *data, char *str, int type)
{
	t_cmd	*head;

	head = data->cmdlist;
	if (!head)
		return (-ft_strlen(str));
	while (head->next)
		head = head->next;
	head->next = ft_newnode();
	if (type == PIPE)
	{
		head->next->infile = head->outfile;
		head->status = PIPE;
	}
	return (1);
}

int	ft_buildnode(t_data *data, char *str, int type)
{
	t_cmd	*head;

	if (!data->cmdlist)
		data->cmdlist = ft_newnode();
	head = data->cmdlist;
	while (head->next)
		head = head->next;
	if (type == WORD && head->status >= OUTFILE && head->status <= INFILE)
		ft_redirection(data, str);
	else if (type == WORD)
	{
		if (!head->path)
			head->path = ft_strdup(str);
		ft_arebuild(data, str);
	}
	return (0);
}
