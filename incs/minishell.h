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
    char **argv;
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
t_cmd *ft_newcmd(void);
char **ft_cmdarray(char **input, char *arg);
int ft_buildword(t_mini *data, char *str);
int ft_buildfd(t_mini *data, char *str, int type);
int ft_buildpipe(t_mini *data, char *str);

// execute.c
int ft_checkcmd(t_mini *data);
int ft_runcmd(t_mini *data);
int ft_iscmd(t_mini *data, char *str, t_cmd *head);

// exit.c
int ft_clearlist(t_mini *data, int res);

// builtin.c
int ft_isbuiltin(t_cmd *cmd, int x);
int ft_echo(t_cmd *cmd, int x);
int ft_pwd(int x);

// pipex.c
void	here_doc_pipe(int ac, char **av, char **paths);
char	**ft_findpath(char **env);
char	*find_bin_path(char *cmd, char **paths);
char	*here_doc(char **av);

// pipex_utils.c
void	ft_pipex(int ac, char **av, char **paths, int i);
void	ft_err(char *err_msg);
void	ft_free(char **str);
void	runcmd(char **paths, char **argv, int dupped_fd, int i);

#endif
