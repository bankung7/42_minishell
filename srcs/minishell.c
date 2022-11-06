#include "minishell.h"

int main(void)
{
	char	*line;
    t_token *token;

    token = 0;
    
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
			// printf("command : %s\n", line);
			ft_tokenize(&token, line);
            // -------------- check token ------------------
            int i = 0;
            t_token *head;
            head = token;
            while (head)
            {
                printf("[%d] string [%s] => type [%d]\n", i++, head->string, head->type);
                head = head->next;
            }
            // -------------- check token ------------------
            if (ft_buildcmd(&token) == -1)
                printf("command error\n");
            ft_cleartoken(&token);
			printf("\n");
        }
		free(line);
	}
	return (0);
}