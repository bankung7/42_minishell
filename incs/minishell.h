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
# define OUTFILE 1
# define APPEND 2
# define INFILE 3
# define HEREDOC 4
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
	int status;
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
char *ft_expander(t_data *data, char *str, int start, int j);

// parser.c
int ft_buildnode(t_data *data, char *str, int type);
t_cmd *ft_newnode(void);
int ft_bpipe(t_data *data, char *str);

// executing.c
int ft_execute(t_data *data);

// builtin
// env.c
char *ft_getenv(t_data *data, char *var);
int ft_env(t_data *data);
int ft_echo(t_cmd *cmd);

// redirection.c
int	ft_redirection(t_data *data, char *file);

// exit.c
int ft_clean(t_data *data, int res);

#endif
