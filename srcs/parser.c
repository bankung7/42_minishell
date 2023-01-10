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

t_cmd *ft_lastcmd(t_cmd *cmd)
{
	t_cmd *head;

	if (cmd == 0)
		return (cmd);
	head = cmd;
	while (head->next)
		head = head->next;
	return (head);
}

int ft_wparser(t_data *data, t_token *token)
{
	t_cmd *head;

	if (data->cmdlist == 0)
		data->cmdlist = ft_newnode();
	head = ft_lastcmd(data->cmdlist);
	char **tmp = malloc(sizeof(char *) * (ft_arrlen(head->argv) + 2));
	if (!tmp)
		return (-1);
	int i = 0;
	while (head->argv && head->argv[i])
	{
		tmp[i] = head->argv[i];
		i++;
	}
	ft_expander(data, token);
	tmp[i++] = ft_strdup(token->str);
	tmp[i] = 0;
	free(head->argv);
	head->argv = tmp;
	if (head->path == 0)
		head->path = ft_strdup(token->str);
	head->status = WORD;
	return (0);
}

// parser pipe
int ft_ppipe(t_data *data, t_token *token)
{
	t_cmd *head;

	head = ft_lastcmd(data->cmdlist);
	if (head == 0 || head->status != WORD || token->next == 0)
	{
		data->status = -1;
		return (-1);
	}
	head->next = ft_newnode();
	return (0);
}

// parser
int ft_parser(t_data *data)
{
	t_token *token;

	token = data->token;						
	while (data->status == 0 && token)
	{
		if (token->type == WORD)
			ft_wparser(data, token);
		else if (token->type >= OUTFILE && token->type <= HEREDOC)
		{
			data->status = ft_redirection(data, token);
			token = token->next;
		}
		else if (token->type == PIPE)
			ft_ppipe(data, token);
		token = token->next;
	}
	// printf("parser status : %d\n", data->status);
	return (0);
}
