/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:03:09 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:03:13 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_subhd(t_data *data, t_token *token, char *input)
{
	char	*tmp;

	if (ft_strchr(token->str, '$') != 0)
		ft_expander(data, token, 1);
	tmp = ft_strjoin(input, token->str);
	free(token->str);
	free(input);
	return (tmp);
}

static char	*heredoc(t_data *data, char *lmt)
{
	char	*str;
	t_token	*token;

	token = malloc(sizeof(t_token));
	write(1, ">", 1);
	token->str = get_next_line(STDIN_FILENO);
	str = 0;
	while (1)
	{
		if (token->str == 0)
			break ;
		str = ft_subhd(data, token, str);
		write(1, ">", 1);
		token->str = get_next_line(STDIN_FILENO);
		if (token->str && ft_strncmp(token->str, lmt, ft_strlen(lmt)) == 0)
		{
			free(token->str);
			break ;
		}
	}
	free(token);
	return (str);
}

static void	hd_child(t_data *data, t_cmd *head, int *p)
{
	char	*input;

	signal(SIGINT, ft_sigheredoc);
	close(p[0]);
	input = heredoc(data, head->hd_lmt);
	ft_putstr_fd(input, p[1]);
	close(p[1]);
	free(input);
	exit(0);
}

void	heredoc_dup(t_data *data, t_cmd *head)
{
	int		status;
	int		p[2];

	status = 0;
	signal(SIGINT, SIG_IGN);
	if (pipe(p) == -1)
	{
		perror("pipe error");
		return ;
	}
	head->pid = fork();
	if (head->pid == -1)
		return ;
	if (head->pid == 0)
		hd_child(data, head, p);
	waitpid(head->pid, &status, 0);
	close(p[1]);
	head->infile = dup(p[0]);
	close(p[0]);
	if (WEXITSTATUS(status) != 0)
	{
		g_status = WEXITSTATUS(status);
		data->status = -1;
		return ;
	}
}
