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
# define GREEN "\033[;32m"
# define WHITE "\033[;37m"

// define delimiter
# define WHITE_SPACE 0
# define PIPE 1
# define OR 2
# define SQUOTE 3
# define DQUOTE 4
# define INFILE 5
# define HEREDOC 6
# define OUTFILE 7
# define APPEND 8
# define COMMAND 99

// define prompt
# define PROMPT "\033[;32mminishell$ \033[;37m"
# define EXIT_MSG "Exiting Bye~"

// structure
typedef struct s_cmd
{
    char **cmd;
    char *path;
    int infile;
    int outfile;
    struct s_cmd *next;
}   t_cmd;

typedef struct s_mini
{
    t_cmd *cmd;
}   t_mini;

// token.c
int ft_tokenize(char *str);

#endif
