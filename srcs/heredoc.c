#include "minishell.h"

void	heredoc_dup(t_data *data, t_cmd *head)
{
	// if (head->hd_lmt != NULL)
	// {
	// 	ft_putstr_fd(heredoc(data, head->hd_lmt), head->hdfd[WR]);
	// 	close(head->hdfd[WR]);
	// 	dup2(head->hdfd[RD], STDIN_FILENO);
	// 	close(head->hdfd[RD]);
	// }
	int status = 0;
    int p[2];
	signal(SIGINT, SIG_IGN);
    pipe(p);
    head->pid = fork();
    if (head->pid == 0)
    {
        signal(SIGINT, ft_sigheredoc);
        close(p[0]);
        ft_putstr_fd(heredoc(data, head->hd_lmt), p[1]);
        close(p[1]);
        exit(0);
    }
    waitpid(head->pid, &status, 0);
    close(p[1]);
    if (WEXITSTATUS(status) != 0)
    {
        close(p[0]);
        g_status = WEXITSTATUS(status);
        data->status = -1;
        return ;
    }
    head->infile = dup(p[0]);
    close(p[0]);
}

char	*heredoc(t_data *data, char *lmt)
{
	char *tmp;
	char *str;
	(void)data;
	t_token *token;

	token = malloc(sizeof(t_token));
	write(1, ">", 1);
	token->str = get_next_line(STDIN_FILENO);
	str = 0;
	while (1)
	{
        if (ft_strchr(token->str, '$') != 0)
            ft_getexpand(data, token, 0);
		tmp = ft_strjoin(str, token->str);
		free(token->str);
        free(str);
		str = tmp;
		write(1, ">", 1);
		token->str = get_next_line(STDIN_FILENO);
		if (ft_strncmp(token->str, lmt, ft_strlen(lmt)) == 0)
			break ;
	}
	return (str);
}

int	ft_heredoc(t_data *data)
{
	t_cmd	*head;

	head = data->cmdlist;
	if (head->hd_lmt != NULL)
		pipe(head->hdfd);
	return (2);
}
