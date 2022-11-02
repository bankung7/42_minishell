#include "minishell.h"

// In this section, There are a handlering for ctrl-C and ctrl- <black slash>
// In interactive mode:
// ctrl-C : display a new prompt on a newline (original is SIGINT)
// ctrl-\ : does nothing (original is SIGQUIT)
// ctrl-D : exits the shell (this is not a signal, it is a EOF)

void	ft_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
		rl_redisplay();
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
