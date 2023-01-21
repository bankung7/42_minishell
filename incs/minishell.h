#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <errno.h>
#include "libft.h"

// PROMPT
#define MPROMPT "\033[0;32mminishell$ \033[0;37m"

// delimiter
#define DELIMITER 0
#define OUTFILE 1
#define APPEND 2
#define INFILE 3
#define HEREDOC 4
#define PIPE 5
#define SQUOTE 11
#define DQUOTE 12
#define DOLLARS 13
#define WORD 100

#define RD 0
#define WR 1

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 4096
#endif

// Global for pipe status
int g_status;

// struct

typedef struct s_expd
{
	char	*tmp;
	char	*env;
	char	*new;
	char	*next;
	char	**stmp;
	int	x;
	int	j;
}	t_expd;
typedef struct s_token
{
	char *str;
	int type;
	int len;
	struct s_token *next;
} t_token;

typedef struct s_cmd
{
	char **argv;
	char *path;
	int infile;
	int outfile;
	int status;
	int pipe;
	int pid;
	int pfd[2];
	int hdfd[2];
	int	lfd[2];
    int pc;
	char *hd_lmt;
	struct s_cmd *next;
} t_cmd;

typedef struct s_data
{
	t_cmd *cmdlist;
	t_token *token;
	char **env;
	int ori_fd[2];
	int status;
	char *line;
	int len;
} t_data;

// ==== PART 1 : Initialize and Preparation ================ //
// signal.c
void    ft_sigchild(int sig);
void    ft_sigheredoc(int sig);
int ft_sighandle(void);

// init.c
int	ft_resetdata(t_data *data);
int ft_initenv(t_data *data, char **env);

// ==== PART 2 : Lexical, Tokenize, Expander and Parser ==== //
// lexical.c
int ft_lexical(t_data *data);

// tokenize.c
int ft_addtoken(t_data *data, char *str, int type);
int ft_reargv(t_data *data, char *str);

// quote.c
int	ft_unquote(t_token *token, int i, int quote);
int	ft_dquote(t_data *data, t_token *token, int i);

// expander.c
int	ft_getexpand(t_data *data, t_token *token, int i);
int ft_expander(t_data *data, t_token *token, int x);

// expander2.c
int	ft_xset(t_expd *stc, t_token *token, int i, t_data *data);
int	ft_xjoin(t_token *token, int i, t_expd *stc);
int	ft_xsplit(t_data *data, t_token *token, int i);

// parser.c
t_cmd *ft_lastcmd(t_cmd *cmd);
t_cmd *ft_newnode(void);
int ft_parser(t_data *data);

// ==== PART 3 : Command and Executing ====================== //
// cmd.c
char *ft_iscmd(t_data *data, t_cmd *cmd);
int ft_builtin(t_data *data, t_cmd *cmd);
int ft_builtin_out(t_data *data, t_cmd *cmd, int mode);
int ft_runcmd(t_data *data, t_cmd *cmd);

// executing.c
int ft_execute(t_data *data);

// ==== PART 4 : Redirection & Pipe ========================== //
// redirection.c
int	ft_reheredoc(t_data *data, t_token *token);
int ft_redirection(t_data *data, t_token *token);

// heredoc.c
void heredoc_dup(t_data *data, t_cmd *head);
char *heredoc(t_data *data, char *str);
int ft_heredoc(t_data *data);

// pipe.c
int pipe_next(t_data *data, t_cmd *head);
int infile_dup(t_data *data, t_cmd *head);
void stdout_dup(t_data *data, t_cmd *head);
void stdin_dup(t_data *data, t_cmd *head);

// ==== PART 5 : Built-in Function ========================== //
// env.c
char *ft_getenv(t_data *data, char *var);
int ft_env(t_data *data);

// echo.c
int ft_echo(t_cmd *cmd);

// pwd.c
int ft_pwd(void);

// cd.c
int ft_cd(t_data *data, t_cmd *cmd, int mode);

// export.c
int ft_arrlen(char **arr);
int ft_export(t_data *data, t_cmd *cmd, int mode);

// unset.c
int ft_unset(t_data *data, t_cmd *cmd, int mode);

// exit.c
int ft_clean(t_data *data, int res);
int ft_exit(t_data *data, int mode);

// ==== PART 6 : Utilities Function ==========================//
// get_next_line.c
char *get_next_line(int fd);
char *get_remain(char *s, int nl_id);
char *get_line(char *s, int nl_id);
char *ft_lastline(char *str);
char *ft_read(char *str, int fd);

// get_next_line_utils.c
int ft_strlen_nl(char *s, int sel);
char *ft_strcpy(char *dst, char *src);

// utils.c
int ft_ttoken(t_data *data);
int	ft_tast(t_data *data);
int ft_print2a(char **arr);

// free.c
int ft_closefd(t_data *data, int res);
int	ft_freecmd(t_cmd *head, int res);
int	ft_freetoken(t_data *data, int res);
int ft_free2(void **arr, int res);
int	ft_freeexpd(t_expd *stc);

#endif
