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

// PROMPT
# define MPROMPT "\033[0;32mminishell$ \033[0;37m"

// delimiter
# define DELIMITER 0
# define INFILE 1
# define HEREDOC 2
# define OUTFILE 3
# define APPEND 4
# define PIPE 5
# define SQUOTE 11
# define DQUOTE 12
# define DOLLARS 13
# define WORD 99

// struct
typedef struct s_cmd
{
	char **argv;
	char *path;
	int infile;
	int outfile;
	int space;
	struct s_cmd *next;
}	t_cmd;


typedef struct	s_data
{
	t_cmd	*cmdlist;
	char	**tray;
	char	**env;
}	t_data;

// signal.c
int	ft_sighandle(void);

// tokenize.c
int ft_isdelimit(char *str, int i);
int ft_tokenize(t_data *data, char *str);

// expander.c
int ft_expander(t_data *data);
char *ft_nexpander(char *str);

// parser.c

// builtin
// env.c
char *ft_getenv(t_data *data, char *var);

#endif
