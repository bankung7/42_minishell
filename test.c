// #include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include "libft.h"

int	main(int ac, char **av)
{
	int	pid[ac - 3];
	int pipes[ac - 4][2]; //3
	int	i;
	char **argv;

	for (i = 0; i < ac - 4; i++)
		pipe(pipes[i]);

	for (i = 0; i < ac - 3; i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			// Child process
			if (i == 0) //first cmd
			{
				close(pipes[i][0]);
				// int infile = open(av[1], O_RDONLY);
				// dup2(infile, STDIN_FILENO);
				dup2(pipes[i][1], STDOUT_FILENO);
				// close(infile);
				close(pipes[i][1]);
			}
			else if (i == ac - 4) //last cmd
			{
				close(pipes[i - 1][1]);
				// int outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0775);
				dup2(pipes[i - 1][0], STDIN_FILENO);
				// dup2(outfile, STDOUT_FILENO);
				// close(outfile);
				close(pipes[i - 1][0]);
			}
			else
			{
				close(pipes[i - 1][1]);
				dup2(pipes[i - 1][0], STDIN_FILENO);
				dup2(pipes[i][1], STDOUT_FILENO);
				close(pipes[i - 1][0]);
				close(pipes[i][1]);
			}
			argv = ft_split(av[i + 1], ' ');
			execlp(argv[0], argv[0], argv[1], NULL);
			return (0);
		}
	}

	// Main process
	while (wait(NULL) != -1 || errno != ECHILD)
	return (0);
}