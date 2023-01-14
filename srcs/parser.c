#include "minishell.h"

t_cmd	*ft_newnode(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->argv = 0;
	node->path = 0;
	node->infile = STDIN_FILENO;
	node->outfile = STDOUT_FILENO;
	node->status = 0;
	node->pipe = 0;
	node->next = 0;
	node->hd_lmt = 0;
	return (node);
}

t_cmd	*ft_lastcmd(t_cmd *cmd)
{
	t_cmd	*head;

	if (cmd == 0)
		return (cmd);
	head = cmd;
	while (head->next)
		head = head->next;
	return (head);
}

int	ft_wparser(t_data *data, t_token *token)
{
	char	**tmp;
	t_cmd	*head;

	if (data->cmdlist == 0)
		data->cmdlist = ft_newnode();
	if (data->cmdlist == 0)
		return (-1);
	head = ft_lastcmd(data->cmdlist);
	tmp = malloc(sizeof(char *) * (ft_arrlen(head->argv) + 2));
	if (!tmp)
		return (-1);
	while (head->argv && head->argv[token->len])
	{
		tmp[token->len] = head->argv[token->len];
		token->len++;
	}
	ft_expander(data, token, 1);
	tmp[token->len++] = ft_strdup(token->str);
	tmp[token->len] = 0;
	free(head->argv);
	head->argv = tmp;
	if (head->path == 0)
		head->path = ft_strdup(token->str);
	head->status = WORD;
	return (0);
}

// parser pipe
// test case if no cmd has to be parsed, just open and close then skip
int	ft_ppipe(t_data *data, t_token *token)
{
	t_cmd	*head;

	head = ft_lastcmd(data->cmdlist);
	if (head == 0 || head->status != WORD || token->next == 0)
	{
		data->status = -1;
		return (-1);
	}
	head->next = ft_newnode();
	if (head->next == 0)
		return (-1);
	if (head->path != 0)
		head->pipe = 1;
	return (0);
}

// parser
int	ft_parser(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (data->status == 0 && token)
	{
		if (token->type == WORD)
			ft_wparser(data, token);
		else if (token->type >= OUTFILE && token->type <= HEREDOC)
		{
			if (token->type == HEREDOC)
				data->status = ft_reheredoc(data, token);
			else
				data->status = ft_redirection(data, token);
			if (data->status != 0)
				break ;
			token = token->next;
		}
		else if (token->type == PIPE)
			data->status = ft_ppipe(data, token);
		token = token->next;
	}
	if (data->status != 0)
		printf("parser error\n");
	return (data->status);
}
