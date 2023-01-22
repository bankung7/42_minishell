/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:03:22 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:03:24 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		printf("tfd\t:\t[%d]\n", head->tfd);
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

int	ft_print2a(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		printf("arr : %s\n", arr[i++]);
	printf("\n");
	return (0);
}

void	ft_error(t_cmd *cmd)
{
	ft_putstr_fd(cmd->argv[0], 2);
	if (ft_strchr(cmd->argv[0], '/') == 0)
		ft_putstr_fd(": command not found\n", 2);
	else if (opendir(cmd->argv[0]) == 0)
		ft_putstr_fd(": no such file or directory\n", 2);
	else
	{
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	exit(127);
}
