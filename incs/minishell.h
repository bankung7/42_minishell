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

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
// Global for pipe status
int g_status;

// struct
typedef struct s_cmd
{
	char **argv;
	char *path;
	int infile;
	int outfile;
	int status;
	int pipe;
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

// init.c
int	ft_initenv(t_data *data, char **env);

// tokenize.c
int ft_isdelimit(char *str, int i);
int ft_tokenize(t_data *data, char *str);

// expander.c
char *ft_expander(t_data *data, char *str, int start, int j);

// parser.c
int ft_buildnode(t_data *data, char *str, int type);
t_cmd *ft_newnode(void);
int ft_bpipe(t_data *data, char *str, int type);

// executing.c
int ft_execute(t_data *data);
int ft_execve(t_data *data, t_cmd *cmd);
int ft_iscmd(t_data *data, t_cmd *cmd);
int ft_runcmd(t_data *data, t_cmd *cmd);

// builtin
// env.c
char *ft_getenv(t_data *data, char *var);
int ft_env(t_data *data);

// echo.c
int ft_echo(t_cmd *cmd);

// pwd.c
int ft_pwd(void);

//cd.c
int	ft_cd(t_data *data, t_cmd *cmd);

// export.c
int ft_export(t_data *data, t_cmd *cmd);

// unset.c
int ft_unset(t_data *data, t_cmd *cmd);

// redirection.c
int	ft_redirection(t_data *data, char *file);

// heredoc.c
int ft_heredoc(t_data *data, char *str);

// pipe.c
int	ft_pipex(t_data *data, t_cmd *head);
int ft_topipe(t_data *data, t_cmd *cmd);

// exit.c
int ft_clean(t_data *data, int res);
int ft_exit(t_data *data);
int ft_freel1(t_data *data, int i);
int ft_free2(void **arr, int res);
int ft_clean1(t_data *data, int res);

//get_next_line.c
char	*get_next_line(int fd);
char	*get_remain(char *s, int nl_id);
char	*get_line(char *s, int nl_id);
char	*ft_lastline(char *str);
char	*ft_read(char *str, int fd);

//get_next_line_utils.c
int		ft_strlen_nl(char *s, int sel);
char	*ft_strcpy(char *dst, char *src);

//heredoc.c
char	*here_doc(char **av);
void	here_doc_pipe(int ac, char **av, char **paths);

#endif
