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
	struct sigaction	acint;
    struct sigaction    acquit;

	acint.sa_sigaction = ft_handler;
	acint.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &acint, 0);
    acquit.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &acquit, 0);
	return (0);
}
