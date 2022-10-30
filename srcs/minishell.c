#include "minishell.h"

int main(void)
{
	char	*line;

	// signaling
	ft_sighandle();

	while (1)
	{
		line = readline("msh $ ");
		if (!line)
		{
			printf("Exiting\n");
			return (0);
		}
		else
			printf("command is : %s\n", line);
		free(line);
	}
	return (0);
}