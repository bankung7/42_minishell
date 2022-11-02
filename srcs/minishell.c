#include "minishell.h"

int main(void)
{
	char	*line;

	// signaling
	ft_sighandle();

    // looping
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
		{
			printf("%s\n", EXIT_MSG);
			return (0);
		}
		else
        {
            // Execute by execv
			printf("command is : %s\n", line);
        }
		free(line);
	}
	return (0);
}