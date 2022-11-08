NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = libft/libft.a

RL_DIR = /usr/local/Homebrew/opt/readline
LIB_DIR = -lreadline
LIB_INC = -Iincs -Ilibft

ifeq ($(shell uname), Darwin)
LIB_DIR += -L$(RL_DIR)/lib
LIB_INC += -I$(RL_DIR)/include
endif

ifeq ($(shell uname), Linux)
LIB_DIR += -L/usr/local/opt/readline/lib -Llibft -lft
LIB_INC += -I/usr/local/opt/readline/include
endif

RM = rm -rf

SRCS_DIR = srcs/
SRCS = minishell.c signal.c token.c parsing.c builtin.c

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
	@echo "minishel is on prepared!"
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(NAME)
	@make clean -C $(LIBFT_DIR)
	@echo "Some clean~"

fclean: clean
	@$(RM) $(OBJS_DIR)
	@make fclean -C $(LIBFT_DIR)
	@echo "All clean~"

re: fclean all

norm:
	norminette -R checkForbiddenSourceHeader $(SRCS_DIR) $(LIBFT_DIR)
	norminette -R checkDefine incs/ $(LIBFT)/libft.h

.PHONY: all clean fclean re norm