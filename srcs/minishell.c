#include "minishell.h"

int main(void)
{
	char	*line;

	// signaling
	//ft_sighandle();

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
			// printf("command is : %s\n", line);
			printf("line len => [%d]\n", (int)ft_strlen(line));
			ft_token(line);
			printf("\n");
        }
		free(line);
	}
	return (0);
}