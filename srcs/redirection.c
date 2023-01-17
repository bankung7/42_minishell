#include "minishell.h"

int	ft_clearfd(t_cmd *head, int type)
{
	if (type == INFILE && head->infile > 2)
		close(head->infile);
	else if ((type == OUTFILE || type == APPEND) && head->outfile > 2)
		close(head->outfile);
	return (0);
}

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
	heredoc_dup(head);
	head->status = WORD;
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
	ft_clearfd(head, token->type);
	if (token->type == INFILE)
		head->infile = open(token->next->str, O_RDONLY);
	else if (token->type == OUTFILE)
		head->outfile = open(token->next->str,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (token->type == APPEND)
		head->outfile = open(token->next->str,
				O_RDWR | O_APPEND | O_CREAT, 0644);
	if (head->infile == -1 || head->outfile == -1)
	{
		perror("nofile ");
		return (-1);
	}
	head->status = WORD;
	return (0);
}
