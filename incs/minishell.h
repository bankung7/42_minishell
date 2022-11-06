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

// define delimiter
# define END_TOKEN -2
# define WORD -1
# define DELIMITER 0
# define PIPE 1
# define OR 2
# define INFILE 3
# define HEREDOC 4
# define OUTFILE 5
# define APPEND 6
# define SQUOTE 8
# define DQUOTE 10
# define DSIGN 9

// structure
typedef struct s_token
{
    int type;
    char *string;
    struct s_token *next;
}   t_token;

typedef struct s_data
{
    t_token *token;
    int is_infile;
    int is_outfile;
}   t_data;

// token
int ft_isdelimit(char *str, int i);
void    ft_tokenize(t_token **token, char *str);
int ft_cleartoken(t_token **token);

// parsing
int ft_buildcmd(t_token **token);

// executing

// signal
int ft_sighandle(void);

// pipe

#endif
