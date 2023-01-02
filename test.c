// #include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
// #include "libft.h"

#define NPROC	3
// int	main(int ac, char **av)
int	main()
{
	int	pid[NPROC];
	// int pipes[ac - 4][2]; //3
	int	i;
	// char **argv;

	// for (i = 0; i < ac - 4; i++) //3
	// 	pipe(pipes[i]);

	for (i = 0; i < NPROC; i++)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			// Child process
			printf("(%d) return : %d\n", i, sleep(3 - i));
			return (0);
		}
	}
	// Main process
	while (wait(NULL) != -1 || errno != ECHILD) ;
	return (0);
}