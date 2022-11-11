/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:19:30 by pjerddee          #+#    #+#             */
/*   Updated: 2022/11/11 21:19:48 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	runcmd(char **paths, char **argv, int dupped_fd, int i);

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
