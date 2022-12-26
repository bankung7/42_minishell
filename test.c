// #include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define	IN 0
#define	OUT 1

int	main()
{
	int	fd[2];
	int	status;
	char	str[100];

	if (pipe(fd) == -1)
	{
		printf("Error at pipe\n");
		return 1;
	}
	int id = fork();
	if (id == 0)
	{
		dup2(fd[OUT], STDOUT_FILENO);
		close(fd[OUT]);
		printf("From child\n");
		exit(0);
	}
	else
	{
		wait(NULL);
		waitpid(id, &status, 0);
		read(fd[OUT], &str, 10);
		printf("IN PARENT-> %s\n", str);
	}
	return (0);
}