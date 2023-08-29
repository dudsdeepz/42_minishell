# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 11:10:51 by eduarodr          #+#    #+#              #
#    Updated: 2023/08/09 14:59:00 by eduarodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -lreadline

RM = rm -f

SOURCES = main.c\
			srcs/init_shell.c\
			srcs/shell_utils.c\
			srcs/builtins.c\
			srcs/utils.c\

LIBFT_PATH = ./libft
LIBFT_NAME = libft.a

$(LIBFT_NAME):
		@make -sC $(LIBFT_PATH)

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME) $(LIBFT_NAME)

$(NAME): $(OBJECTS)
	@echo "\033[4;33m[+] Compiling..\033[1;0m"
	$(CC) $(CFLAGS) $(SOURCES) -o ${NAME} ./libft/${LIBFT_NAME} -lreadline
	@echo "\033[4;32m[✓] Ready!\033[1;0m"

clean:
	@echo "\033[4;33m[+] Cleaning objects..\033[1;0m"
	$(RM) $(OBJECTS)
	@echo "\e[4;32m[✓]Objects cleaned!\033[1;0m"

fclean: clean
	@echo "\033[4;33m[+] Cleaning functions..\033[1;0m"
	$(RM) $(NAME) minishell
	@echo "\033[4;32m[✓]Functions cleaned!\033[1;0m"

re: fclean all

.PHONY: all clean fclean re