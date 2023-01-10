#include "minishell.h"

// int	ft_redirection(t_data *data, char *file)
// {
// 	t_cmd	*head;

// 	head = data->cmdlist;
// 	while (head->next)
// 		head = head->next;
// 	if (head->status == INFILE)
// 		head->infile = open(file, O_RDONLY);
// 	else if (head->status == OUTFILE)
// 		head->outfile = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	else if (head->status == APPEND)
// 		head->outfile = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
// 	//Is these part needed??
// 	// if (head->infile < 0 || head->outfile < 0)
// 	// 	return (-1);
// 	head->status = 0;
// 	free(file);
// 	return (0);
// }

// redirection
int ft_redirection(t_data *data, t_token *token)
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