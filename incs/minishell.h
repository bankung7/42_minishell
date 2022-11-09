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
# define ERROR -1
# define WHITE_SPACE 0
# define PIPE 1
# define OR 2
# define INFILE 3
# define HEREDOC 4
# define OUTFILE 5
# define APPEND 6
# define SQUOTE 11
# define DQUOTE 12
# define SWORD 97
# define WORD 98
# define COMMAND 99
# define BUILTIN 100

// define prompt
# define PROMPT "\033[;32mminishell$ \033[;37m"
# define EXIT_MSG "Exiting Bye~"

// structure
typedef struct s_cmd
{
    char **vector;
    char *cmd;
    char *path;
    int infile;
    int outfile;
    int type;
    struct s_cmd *next;
}   t_cmd;

typedef struct s_mini
{
    t_cmd *cmdlist;
}   t_mini;

// token.c
int ft_tokenize(t_mini *data, char *str);

// parsing.c
int ft_buildlist(t_mini *data, char *str, int type);
int ft_checkcmd(t_mini *data);

#endif
