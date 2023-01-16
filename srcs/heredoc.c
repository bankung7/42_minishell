#include "minishell.h"

void	heredoc_dup(t_cmd *head)
{
	if (head->hd_lmt != NULL)
	{
		ft_putstr_fd(heredoc(head->hd_lmt), head->hdfd[WR]);
		close(head->hdfd[WR]);
		dup2(head->hdfd[RD], STDIN_FILENO);
		close(head->hdfd[RD]);
	}
}

char	*heredoc(char *str)
{
	char	*limiter;
	char	*line;
	char	*input_s;
	char	*tmp_input_s;

	limiter = ft_strjoin(str, "\n");
	write(1, ">", 1);
	line = get_next_line(0);
	input_s = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	while (ft_strncmp(line, limiter, ft_strlen(limiter)))
	{
		write(1, ">", 1);
		tmp_input_s = input_s;
		input_s = ft_strjoin(input_s, line);
		free(tmp_input_s);
		line = get_next_line(0);
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
