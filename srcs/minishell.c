#include "minishell.h"

int main(void)
{
	char	*line;

	ft_sighandle();

	while (1)
	{
		line = readline("msh $ ");
		if (ft_strlen(line) == 0)
		{
			printf("this case\n");
			free(line);
			write(1, "\n", 1);
			break ;
		}
		printf("command is : %s - length : %d\n", line, (int)ft_strlen(line));
		free(line);
	}
	return (0);
}