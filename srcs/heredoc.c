#include "minishell.h"

// void	here_doc_pipe(int ac, char **av, char **paths)
// {
// 	int		hd_fd[2];

// 	if (pipe(hd_fd) != 0)
// 	{
// 		ft_free(paths);
// 		ft_err("Error at pipe\n");
// 	}
// 	else
// 	{
// 		ft_putstr_fd(here_doc(av), hd_fd[1]);
// 		dup2(hd_fd[0], 0);
// 		close(hd_fd[0]);
// 		close(hd_fd[1]);
// 		ft_pipex(ac, av, paths, 3);
// 	}
// }

// char	*here_doc(char **av)
// {
// 	char	*limiter;
// 	char	*line;
// 	char	*input_s;
// 	char	*tmp_input_s;

// 	limiter = ft_strjoin(av[2], "\n");
// 	write(1, ">", 1);
// 	line = get_next_line(0);
// 	input_s = ft_calloc(ft_strlen(line) + 1, sizeof(char));
// 	while (ft_strncmp(line, limiter, ft_strlen(av[2])))
// 	{
// 		write(1, ">", 1);
// 		tmp_input_s = input_s;
// 		input_s = ft_strjoin(input_s, line);
// 		free(tmp_input_s);
// 		line = get_next_line(0);
// 	}
// 	free(limiter);
// 	return (input_s);
// }