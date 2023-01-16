#include "minishell.h"

// In this section, There are a handlering for ctrl-C and ctrl- <black slash>
// In interactive mode:
// ctrl-C : display a new prompt on a newline (original is SIGINT)
// ctrl-\ : does nothing (original is SIGQUIT)
// ctrl-D : exits the shell (this is not a signal, it is a EOF)

void	ft_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_status = 130;
	return ;
}

// modify signal
int	ft_sighandle(void)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
