# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eduarodr <eduarodr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/24 20:18:20 by eduardo           #+#    #+#              #
#    Updated: 2022/11/10 14:43:29 by eduarodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	ft_strlcat.c\
		ft_atoi.c\
		ft_isascii.c\
		ft_memcpy.c\
		ft_bzero.c\
		ft_isdigit.c\
		ft_memmove.c\
		ft_calloc.c\
		ft_isprint.c\
		ft_memset.c\
		ft_strlen.c\
		ft_isalnum.c\
		ft_memchr.c\
		ft_strncmp.c\
		ft_isalpha.c\
		ft_memcmp.c\
		ft_strlcpy.c\
		ft_strnstr.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strdup.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_strmapi.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_striteri.c\

BONUS = 	ft_lstnew.c\
			ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstlast.c\
			ft_lstadd_back.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c\

OBJ	=	$(SRC:.c=.o)

B_OBJ = $(BONUS:.c=.o)

NAME	=	libft.a

CC	=	cc

SO	=	libft.so

RM	=	rm -f

CFLAGS	=	-Wall -Werror -Wextra -I.

all:	$(NAME)

$(NAME):	$(OBJ)
		ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
		$(RM) $(NAME)

re:	fclean $(NAME)

bonus:	$(OBJ)	$(B_OBJ)
		ar rcs $(NAME)	$(OBJ)	$(B_OBJ)

.PHONY: all clean fclean re
