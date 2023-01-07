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
int ft_expander1(t_data *data, t_token *token);

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
	// if (data->status != 0)
	// 	printf("quote error\n");
	// ft_ttoken(data);
	// printf("lexical status : %d\n", data->status);
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
	ft_expander1(data, token);
	tmp[i++] = ft_strdup(token->str);
	tmp[i] = 0;
	free(head->argv);
	head->argv = tmp;
	if (head->path == 0)
		head->path = ft_strdup(token->str);
	head->status = WORD;
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
	// after redirection and pipe it seem work like no pipe
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
	// printf("parser status : %d\n", data->status);
	return (0);
}

/////////////////////////////////////////////////////////

int ft_unquote(t_token *token, int i, int quote)
{
	int j;

	j = 1;
	// printf("to unquote : %s\n", &token->str[i]);
	ft_memmove(&token->str[i], &token->str[i + j], ft_strlen(token->str) - (i + j) + 1);
	// printf("first move : %s\n", &token->str[i]);
	while (token->str[i + j] && token->str[i + j] != quote)
		j++;
	if (token->str[i + j] == 0)
		token->str[i] = 0;
	else
		ft_memmove(&token->str[i + j], &token->str[i + j + 1], ft_strlen(token->str) - (i + j));
	return (j);
}

int ft_getexpand(t_data *data, t_token *token, int i)
{
	int j;

	j = 1;
	while (token->str[i + j] && (ft_isalnum(token->str[i + j]) == 1 || token->str[i + j] == '_'))
		j++;
	char *tmp = ft_substr(token->str, i + 1, j - 1);
	char *env = ft_getenv(data, tmp);
	// printf("tmp %s : %s\n", tmp, env);
	char *new = ft_calloc(sizeof(char), ft_strlen(token->str) + (ft_strlen(env) - ft_strlen(tmp)) + 1);
	ft_memcpy(new, token->str, i);
	ft_memcpy(&new[ft_strlen(new)], env, ft_strlen(env));
	ft_memcpy(&new[ft_strlen(new)], &token->str[i + j], ft_strlen(token->str) - (i + j));
	// printf("new : %s\n", new);
	// free(new);
	free(tmp);
	free(env);
	free(token->str);
	token->str = new;
	return (ft_strlen(env));
}

int ft_dquote(t_data *data, t_token *token, int i)
{
	int j;

	j = 1;
	while (token->str[i + j] && token->str[i + j] != '"')
	{
		if (token->str[i + j] == '$')
			j += ft_getexpand(data, token, i + j);
		j++;
	}
	ft_unquote(token, i, '"');
	return (j - 1);
}

int ft_expander1(t_data *data, t_token *token)
{
	int i;
	(void)data;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '\'')
			i += ft_unquote(token, i, '\'');
		else if (token->str[i] == '"')
			i += ft_dquote(data, token, i);
		else if (token->str[i] == '$')
			i += ft_getexpand(data, token, i);
		else
			i++;
	}
	// printf("after expanded : %s\n", token->str);
	return (0);
}

//  "golf$USER'golf'"