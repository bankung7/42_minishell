#include "minishell.h"

int ft_pwd(void)
{
	char *str;

	str = ft_calloc(sizeof(char), 1024);
	if (!str)
		return (-1);
	if (getcwd(str, 1023) == NULL)
		perror("getcwd() error");
	else
		printf("current working directory is: %s\n", str);
	return (0);
}