#include "minishell.h"

int ft_addtoken(t_data *data, char *str, int type)
{
	t_token *node;
	t_token *head;

	node = malloc(sizeof(t_token));
	if (!node)
		return (-1);
	node->str = str;
	node->type = type;
	node->next = 0;
	if (data->token == 0)
		data->token = node;
	else
	{
		head = data->token;
		while (head->next)
			head = head->next;
		head->next = node;
	}
	return (0);
}

int ft_ctype(t_data *data)
{

	if (ft_strncmp(&data->line[data->len], ">>", 2) == 0)
		return (APPEND);
	if (ft_strncmp(&data->line[data->len], "<<", 2) == 0)
		return (HEREDOC);
	if (data->line[data->len] == '>')
		return (OUTFILE);
	if (data->line[data->len] == '<')
		return (INFILE);
	if (data->line[data->len] == '|')
		return (PIPE);
	if (data->line[data->len] == ' ' || data->line[data->len] == '\t' || data->line[data->len] == '\n')
		return (DELIMITER);
	if (data->line[data->len] == '\'')
		return (SQUOTE);
	if (data->line[data->len] == '"')
		return (DQUOTE);
	return (100);
}

int ft_cquote(t_data *data, int type)
{
	int i;

	data->len++;
	while (data->line[data->len])
	{
		i = ft_ctype(data);
		if (i == type)
			break;
		data->len++;
	}
	if (data->line[data->len] == 0 && (i != type))
		data->status = -1;
	return (0);
}

int ft_wlexical(t_data *data)
{
	int i;
	int type;

	i = data->len;
	while (data->status == 0 && data->line[data->len])
	{
		type = ft_ctype(data);
		if (type == 11 || type == 12)
			ft_cquote(data, type);
		else if (type <= 5)
			break;
		data->len++;
	}
	if (data->status == 0)
		data->status = ft_addtoken(data, ft_substr(data->line, i, data->len - i), WORD);
	return (data->status);
}

// get schar to token
int ft_slexical(t_data *data, int type)
{
	int len;

	len = ((type + 1) % 2) + 1;
	data->status = ft_addtoken(data, ft_substr(data->line, data->len, len), type);
	data->len += len;
	return (data->status);
}

// test token
int ft_ttoken(t_data *data)
{
	t_token *token;
	token = data->token;
	while (token)
	{
		if (data->status == 0)
			printf("%s [%d] ", token->str, token->type);
		token = token->next;
		if (data->token->str)
			free(data->token->str);
		free(data->token);
		data->token = token;
	}
	printf("\n");
	data->token = 0;
	return (0);
}

// define
int ft_parser1(t_data *data);

// check each char and send to tokenize
int ft_lexical(t_data *data)
{
	int type;

	while (data->line[data->len] && data->status == 0)
	{
		type = ft_ctype(data);
		if (type >= 11)
			ft_wlexical(data);
		else if (type >= 1)
			ft_slexical(data, type);
		else
			data->len++;
	}
	if (data->status != 0)
		printf("quote error\n");
	// ft_ttoken(data);
	ft_parser1(data);
	return (0);
}

///////////////////////////////////////////////////

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
	tmp[i++] = ft_strdup(token->str);
	tmp[i] = 0;
	free(head->argv);
	head->argv = tmp;
	if (head->path == 0)
		head->path = ft_strdup(token->str);
	return (0);
}

// redirection
int ft_redi(t_data *data, t_token *token)
{
	t_cmd *head;

	if (!token->next || !token->next->str || token->next->type != WORD)
		return (-1);
	if (data->cmdlist == 0)
		data->cmdlist = ft_newnode();
	head = ft_lastcmd(data->cmdlist);
	if (token->type == INFILE)
		head->infile = open(token->next->str, O_RDONLY);
	else if (token->type == OUTFILE)
		head->outfile = open(token->next->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (token->type == APPEND)
		head->outfile = open(token->next->str, O_RDWR | O_APPEND | O_CREAT, 0644);
	else if (token->type == HEREDOC)
	{
		head->hd_lmt = token->next->str;
		ft_heredoc(data, token->next->str);
	}
	if (head->infile == -1 || head->outfile == -1)
		return (-1);
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
int ft_parser1(t_data *data)
{
	t_token *token;

	token = data->token;
	while (data->status == 0 && token)
	{
		if (token->type == WORD)
			ft_wparser(data, token);
		else if (token->type >= OUTFILE && token->type <= HEREDOC)
		{
			data->status = ft_redi(data, token);
			token = token->next;
		}
		else if (token->type == PIPE)
			ft_ppipe(data, token);
		token = token->next;
	}
	if (data->status == -1)
		printf("parser error\n");
	return (0);
}