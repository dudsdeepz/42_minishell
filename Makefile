# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 11:10:51 by eduarodr          #+#    #+#              #
#    Updated: 2023/10/03 14:44:59 by eduarodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

RM = rm -f

SOURCES = main.c\
			srcs/init_shell.c\
			srcs/shell_utils.c\
			srcs/builtins.c\
			srcs/utils.c\
			srcs/parsing.c\

OBJECTS = $(SOURCES:.c=.o)

LIBFT_PATH = ./libft
LIBFT_NAME = libft.a

all: $(NAME) $(LIBFT_NAME)

$(LIBFT_NAME):
		@make -sC $(LIBFT_PATH)


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
