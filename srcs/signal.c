#include "minishell.h"

// In this section, There are a handlering for ctrl-C, ctrl-D and ctrl-\\
// In interactive mode:
// ctrl-C : display a new prompt on a newline (original is sigint)
// ctrl-D : exits the shell (this is not a signal, it is a EOF)
// ctrl-\ : does nothing (original is sigquit)

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
		printf("this is a SIGINT captured\n");
	else if (sig == SIGQUIT)
		return ;
	return ;
}

int	ft_sighandle(void)
{
	struct sigaction	action;

	action.sa_sigaction = ft_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &action, 0);
	sigaction(SIGQUIT, &action, 0);
	return (0);
}
