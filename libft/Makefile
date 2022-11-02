# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 18:18:35 by vnilprap          #+#    #+#              #
#    Updated: 2022/07/19 12:52:36 by vnilprap         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
       ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
       ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
       ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
       ft_strtrim.c ft_split.c ft_itoa.c ft_putchar_fd.c ft_putstr_fd.c \
       ft_putnbr_fd.c ft_striteri.c ft_strmapi.c \
	   get_next_line.c

SRCS_B = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	     ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	     ft_lstmap.c

OBJS_DIR = obj/

OBJS = $(addprefix $(OBJS_DIR),$(SRCS:.c=.o))
OBJS_B = $(addprefix $(OBJS_DIR),$(SRCS_B:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: $(NAME)

bonus: $(OBJS_B) $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "Libft is ready"

$(OBJS_DIR)%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME) test

re: fclean all

.PHONY: all clean fclean re