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
typedef struct s_token
{
    char *str;
    int type;
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
    char *hd_lmt;
    struct s_cmd *next;
} t_cmd;

typedef struct s_data
{
    t_cmd *cmdlist;
    char **tray;
    char **env;
    int ori_fd[2];
    int status;
    char *line;
    int len;
    t_token *token;
} t_data;

// ==== PART 1 : Initialize and Preparation ================ //
// signal.c
int ft_sighandle(void);

// init.c
int ft_initenv(t_data *data, char **env);

// ==== PART 2 : Lexical, Tokenize, Expander and Parser ==== //
// lexical.c
int ft_lexical(t_data *data);

// tokenize.c
int ft_ttoken(t_data *data);
int ft_addtoken(t_data *data, char *str, int type);

// expander.c
int ft_expander(t_data *data, t_token *token);

// parser.c
t_cmd *ft_lastcmd(t_cmd *cmd);
t_cmd *ft_newnode(void);
int ft_parser(t_data *data);

// ==== PART 3 : Command and Executing ====================== //
// cmd.c
char *ft_iscmd(t_data *data, t_cmd *cmd);
int ft_builtin(t_data *data, t_cmd *cmd);
int ft_builtin_out(t_data *data, t_cmd *cmd);
int ft_runcmd(t_data *data, t_cmd *cmd);

// executing.c
int ft_execute(t_data *data);

// ==== PART 4 : Helper Function ============================ //
// redirection.c
int ft_redirection(t_data *data, t_token *token);

// heredoc.c
void heredoc_dup(t_cmd *head);
char *heredoc(char *str);
int ft_heredoc(t_data *data);

// pipe.c
int pipe_next(t_data *data, t_cmd *head);
int infile_dup(t_data *data, t_cmd *head);
void stdout_dup(t_data *data, t_cmd *head);
void stdin_dup(t_data *data, t_cmd *head);

// get_next_line.c
char *get_next_line(int fd);
char *get_remain(char *s, int nl_id);
char *get_line(char *s, int nl_id);
char *ft_lastline(char *str);
char *ft_read(char *str, int fd);

// get_next_line_utils.c
int ft_strlen_nl(char *s, int sel);
char *ft_strcpy(char *dst, char *src);

// ==== PART 5 : Built-in Function ========================== //
// env.c
char *ft_getenv(t_data *data, char *var);
int ft_env(t_data *data);

// echo.c
int ft_echo(t_cmd *cmd);

// pwd.c
int ft_pwd(void);

// cd.c
int ft_cd(t_data *data, t_cmd *cmd);

// export.c
int ft_arrlen(char **arr);
int ft_export(t_data *data, t_cmd *cmd);

// unset.c
int ft_unset(t_data *data, t_cmd *cmd);

// exit.c
int ft_clean(t_data *data, int res);
int ft_exit(t_data *data);
int ft_freel1(t_data *data, int i);
int ft_free2(void **arr, int res);
int ft_clean1(t_data *data, int res);

#endif
