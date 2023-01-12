// // // #include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int	main()
{
	printf("%d\n", access(NULL, F_OK | X_OK));
}
