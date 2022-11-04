#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

// define color
# define WHITE '\033[;37m'
# define GREEN '\033[;32m'

// define prompt
# define PROMPT "\033[;32mminishell$ \033[;37m"
# define EXIT_MSG "Exiting Bye~"

// define token type
# define END_TOKEN 0
# define WORD 1

// structure
typedef struct s_token
{
    int type;
    char **string;
    struct t_token *next;
}   t_token;

// token
int ft_isdelimit(char *str, int i);
void    ft_token(char *str);

// executing

// signal
int ft_sighandle(void);

// pipe

#endif
