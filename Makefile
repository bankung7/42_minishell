# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 21:03:08 by vnilprap          #+#    #+#              #
#    Updated: 2023/01/22 21:11:43 by vnilprap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS =

LIBFT_DIR = libft
LIBFT = libft/libft.a

RL_DIR = /usr/local/opt/readline
LIB_DIR = -lreadline
LIB_INC = -Iincs -Ilibft -Itester

ifeq ($(shell uname), Darwin)
LIB_DIR += -L$(RL_DIR)/lib -L/usr/local/Homebrew/opt/readline/lib
LIB_INC += -I$(RL_DIR)/include -I/usr/local/Homebrew/opt/readline/include
endif

ifeq ($(shell uname), Linux)
LIB_DIR += -L/usr/local/opt/readline/lib -Llibft -lft
LIB_INC += -I/usr/local/opt/readline/include
endif

RM = rm -rf

SRCS_DIR = srcs/
SRCS = minishell.c signal.c init.c \
	lexical.c tokenize.c expander.c expander2.c parser.c \
	executing.c cmd.c \
	redirection.c pipe.c heredoc.c  quote.c \
	echo.c pwd.c env.c export.c unset.c cd.c exit.c \
	utils.c free.c
	# get_next_line.c get_next_line_utils.c 

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $@  $(LIB_DIR)
	@echo "minishell is ready~"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(LIB_INC) -c $^ -o $@

$(LIBFT):
	@echo "minishell is on prepared!"
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) -rf $(NAME) *.dSYM 
	@make clean -C $(LIBFT_DIR)
	@echo "Some clean~"

fclean: clean
	@$(RM) $(OBJS_DIR)
	@make fclean -C $(LIBFT_DIR)
	@echo "All clean~"

re: fclean all

restart: $(OBJS)
	@$(CC) $(CFLAGS) $^ -o $(NAME)  $(LIB_DIR)

norm:
	norminette -R checkForbiddenSourceHeader $(SRCS_DIR) $(LIBFT_DIR)
	norminette -R checkDefine incs/ $(LIBFT)/libft.h

.PHONY: all clean fclean re restart norm
