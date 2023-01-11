#include "minishell.h"

// Test AST
int	ft_tast(t_data *data)
{
	t_cmd	*head;
	int		i;

	head = data->cmdlist;
	while (head)
	{
		printf("\n===== node ======\n");
		printf("argv\t:\t");
		i = 0;
		while (head->argv && head->argv[i])
			printf("[%s] ", head->argv[i++]);
		printf("\n");
		printf("path\t:\t[%s]\n", head->path);
		printf("infile fd\t:\t[%d]\n", head->infile);
		printf("outfile fd\t:\t[%d]\n", head->outfile);
		printf("pipe\t:\t[%d]\n", head->pipe);
		printf("status\t:\t[%d]\n", head->status);
		printf("heredeoc limiter\t:\t[%s]\n", head->hd_lmt);
		printf("======= end node =======\n");
		head = head->next;
	}
	return (0);
}

// test token
int	ft_ttoken(t_data *data)
{
	t_token	*token;

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
