# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/25 11:10:51 by eduarodr          #+#    #+#              #
#    Updated: 2023/12/01 15:20:57 by eduarodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(VERBOSE).SILENT:

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

RM = rm -f

SOURCES = main.c\
			srcs/shell/init_shell.c\
			srcs/shell/shell_utils.c\
			srcs/shell/shell_utils2.c\
			srcs/shell/shell_utils3.c\
			srcs/parsing/parsing.c\
			srcs/parsing/parsing_checks.c\
			srcs/expansion/expansion.c\
			srcs/expansion/expansion_utils.c\
			srcs/expansion/expansion_utils2.c\
			srcs/expansion/expansion_utils3.c\
			srcs/executor/executor.c\
			srcs/executor/redirections.c\
			srcs/builtins/builtins.c\
			srcs/builtins/export.c\
			srcs/builtins/export_util.c\
			srcs/builtins/export_utils2.c\
			srcs/builtins/cd.c\
			srcs/builtins/unset.c\
			srcs/builtins/echo.c\
			srcs/builtins/exit.c\
			srcs/utils/utils.c\
			srcs/utils/utils2.c\
			srcs/utils/utils3.c\
			srcs/utils/utils4.c\
			srcs/utils/utils5.c\
			srcs/gnl/get_next_line.c\
			srcs/gnl/get_next_line_utils.c\

OBJECTS = $(SOURCES:.c=.o)

LIBFT_PATH = ./libft
LIBFT_NAME = $(addprefix $(LIBFT_PATH)/, libft.a)

all: $(NAME)

$(LIBFT_NAME):
		@make -sC $(LIBFT_PATH)

$(NAME): $(OBJECTS) $(LIBFT_NAME)
	@echo "\033[4;33m[+] Compiling..\033[1;0m"
	make -C $(LIBFT_PATH)
	$(CC) $(CFLAGS) $(SOURCES) -o ${NAME} ${LIBFT_NAME} -lreadline
	@echo "\033[4;32m[✓] Ready!\033[1;0m"


clean:
	@echo "\033[4;33m[+] Cleaning objects..\033[1;0m"
	$(RM) $(OBJECTS)
	make clean -C $(LIBFT_PATH)
	@echo "\e[4;32m[✓]Objects cleaned!\033[1;0m"

fclean: clean
	@echo "\033[4;33m[+] Cleaning functions..\033[1;0m"
	$(RM) $(NAME) minishell
	make fclean -C $(LIBFT_PATH)
	@echo "\033[4;32m[✓]Functions cleaned!\033[1;0m"

re: fclean all

r:
	make re && make clean && clear && ./minishell

.PHONY: all clean fclean re
