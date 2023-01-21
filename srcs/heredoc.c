#include "minishell.h"

void	heredoc_dup(t_data *data, t_cmd *head)
{
	if (head->hd_lmt != NULL)
	{
		ft_putstr_fd(heredoc(data, head->hd_lmt), head->hdfd[WR]);
		close(head->hdfd[WR]);
		dup2(head->hdfd[RD], STDIN_FILENO);
		close(head->hdfd[RD]);
	}
}

char	*heredoc(t_data *data, char *str)
{
	t_token token;
	char	*limiter;
	char	*input_s;
	char	*tmp_input_s;


	limiter = ft_strjoin(str, "\n");
	write(1, ">", 1);
	token.str = get_next_line(STDIN_FILENO);
	input_s = ft_calloc(ft_strlen(token.str) + 1, sizeof(char));
	while (ft_strncmp(token.str, limiter, ft_strlen(limiter)))
	{
		ft_getexpand(data, &token, 0);
		write(1, ">", 1);
		tmp_input_s = input_s;
		input_s = ft_strjoin(input_s, token.str);
		free(tmp_input_s);
		free(token.str);
		token.str = get_next_line(0);
	}
	free(limiter);
	return (input_s);
}

int	ft_heredoc(t_data *data)
{
	t_cmd	*head;

	head = data->cmdlist;
	if (head->hd_lmt != NULL)
		pipe(head->hdfd);
	return (2);
}
