#include "minishell.h"

int	ft_closefd(t_data *data, int res)
{
	dup2(data->ori_fd[RD], STDIN_FILENO);
	dup2(data->ori_fd[WR], STDOUT_FILENO);
	close(data->ori_fd[WR]);
	close(data->ori_fd[RD]);
	return (res);
}

int	ft_free2(void **arr, int res)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
	return (res);
}

int	ft_freecmd(t_cmd *head, int res)
{
	if (head->argv)
		ft_free2((void **)head->argv, 0);
	if (head->path)
		free(head->path);
	if (head->hd_lmt)
		free(head->hd_lmt);
	if (head->infile > 2)
		close(head->infile);
	if (head->outfile > 2)
		close(head->outfile);
	return (res);
}

int	ft_freetoken(t_data *data, int res)
{
	t_token	*token;

	token = data->token;
	if (token == 0)
		return (0);
	while (token)
	{
		if (token->str)
			free(token->str);
		if (token->tmp)
			free(token->tmp);
		if (token->env)
			free(token->env);
		if (token->new)
			free(token->new);
		token = token->next;
	}
	data->status = res;
	return (res);
}
