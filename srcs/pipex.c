/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:28 by pjerddee          #+#    #+#             */
/*   Updated: 2022/11/12 16:29:33 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*here_doc(char **av);
void	here_doc_pipe(int ac, char **av, char **paths);

// int	main(int argc, char **argv, char **env)
// {
// 	char	**paths;

// 	if (argc < 5)
// 		ft_putstr_fd("Not enough arguments\n", 2);
// 	else
// 	{
// 		paths = ft_findpath(env);
// 		if (!paths)
// 			ft_putstr_fd("Environment path not found\n", 2);
// 		else if (ft_strncmp(argv[1], "here_doc", 8) == 0)
// 			here_doc_pipe(argc, argv, paths);
// 		else
// 		{
// 			if (open(argv[1], O_RDONLY) < 0)
// 				ft_putstr_fd("File not found", 2);
// 			else
// 			{
// 				dup2(open(argv[1], O_RDONLY), 0);
// 				ft_pipex(argc, argv, paths, 2);
// 			}
// 		}
// 		ft_free(paths);
// 	}
// 	return (0);
// }

void	here_doc_pipe(int ac, char **av, char **paths)
{
	int		hd_fd[2];

	if (pipe(hd_fd) != 0)
	{
		ft_free(paths);
		ft_err("Error at pipe\n");
	}
	else
	{
		ft_putstr_fd(here_doc(av), hd_fd[1]);
		dup2(hd_fd[0], 0);
		close(hd_fd[0]);
		close(hd_fd[1]);
		ft_pipex(ac, av, paths, 3);
	}
}

// char	**ft_findpath(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		if (ft_strnstr(env[i], "PATH=", 5))
// 		{
// 			env[i] = env[i] + 5;
// 			return (ft_split(env[i], ':'));
// 		}
// 		else
// 			i++;
// 	}
// 	return (NULL);
// }

char	*find_bin_path(char *cmd, char **paths)
{
	char	*bin_path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		bin_path = ft_strjoin(paths[i], ft_strjoin("/", cmd));
		if (access(bin_path, X_OK | R_OK | F_OK) == 0)
			return (bin_path);
		else
			i++;
		free(bin_path);
		bin_path = NULL;
	}
	return (NULL);
}

char	*here_doc(char **av)
{
	char	*limiter;
	char	*line;
	char	*input_s;
	char	*tmp_input_s;

	limiter = ft_strjoin(av[2], "\n");
	write(1, ">", 1);
	line = get_next_line(0);
	input_s = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	while (ft_strncmp(line, limiter, ft_strlen(av[2])))
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
