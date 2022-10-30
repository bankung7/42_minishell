NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RLINE_DIR = /opt/homebrew/Cellar/readline/8.1.2
O_LINK = -L$(RLINE_DIR)/lib -lreadline

LIBFT_DIR = libft
LIBFT = libft/libft.a

RM = rm -rf

INC = -Iincs -Ilibft -I$(RLINE_DIR)/include

SRCS_DIR = srcs/
SRCS = minishell.c signal.c

OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(O_LINK) $^ -o $@
	@echo "minishell is ready~"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $^ $(INC) -c -o $@

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