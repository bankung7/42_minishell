#include "minishell.h"

int main(void)
{
	char *line;

	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			continue;
		ft_tokenize(line);
		free(line);
		printf("\n");
	}
	return (0);
}