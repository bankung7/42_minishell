/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:28 by pjerddee          #+#    #+#             */
/*   Updated: 2022/11/13 18:57:41 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_pipex(int ac, char **av, char **paths, int i)
{
	int		fd[2];
	int		pid;

	if (pipe(fd) != 0)
		ft_err("Error at pipe\n");
	pid = fork();
	if (pid < 0)
		ft_err("Error at fork\n");
	else if (pid == 0)
		runcmd(paths, av, fd[1], i);
	else
	{
		wait(NULL);
		close(fd[1]);
		dup2(fd[0], 0);
		if (++i < ac - 2)
			ft_pipex(ac, av, paths, i);
		else
			runcmd(paths, av, open(av[ac - 1], O_WRONLY | O_CREAT, 0775), i);
	}
}

void	ft_err(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	runcmd(char **paths, char **argv, int dupped_fd, int i)
{
	char	**args;
	char	*bin_path;

	args = ft_split(argv[i], ' ');
	bin_path = find_bin_path(args[0], paths);
	if (!bin_path)
	{
		ft_free(args);
		free(bin_path);
		return (ft_putstr_fd("Command not found\n", 2));
	}
	dup2(dupped_fd, 1);
	execve(bin_path, args, NULL);
	free(bin_path);
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
