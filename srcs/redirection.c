#include "minishell.h"

int	ft_reheredoc(t_data *data, t_token *token)
{
	t_cmd	*head;

	if (!token->next || !token->next->str || token->next->type != WORD)
		return (-1);
	if (data->cmdlist == 0)
		data->cmdlist = ft_newnode();
	head = ft_lastcmd(data->cmdlist);
	ft_expander(data, token->next, 0);
	head->hd_lmt = token->next->str;
	ft_heredoc(data);
	return (0);
}

int	ft_redirection(t_data *data, t_token *token)
{
	t_cmd	*head;

	if (!token->next || !token->next->str || token->next->type != WORD)
		return (-1);
	if (data->cmdlist == 0)
		data->cmdlist = ft_newnode();
	head = ft_lastcmd(data->cmdlist);
	ft_expander(data, token->next, 1);
	if (token->type == INFILE)
		head->infile = open(token->next->str, O_RDONLY);
	else if (token->type == OUTFILE)
		head->outfile = open(token->next->str,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (token->type == APPEND)
		head->outfile = open(token->next->str,
				O_RDWR | O_APPEND | O_CREAT, 0644);
	if (head->infile == -1 || head->outfile == -1)
		return (-1);
	head->status = WORD;
	return (0);
}
