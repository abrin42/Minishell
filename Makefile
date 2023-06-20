# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/16 12:55:50 by tmarie            #+#    #+#              #
#    Updated: 2023/06/17 18:24:23 by tmarie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	main.c		\
		function.c	\
		command.c	\
		tri_line.c	\
		ft_command.c \
		parsing.c

SRC_H = minishell.h

OBJ	=	${SRC:.c=.o}

NAME	=	minishell

FLAGS	=	-Wall -Wextra -Werror -g3

FLAGS_PROJECT = -lreadline

all : ${NAME}

$(NAME) : ${OBJ}
	gcc ${FLAGS} ${OBJ} ${SRC_H} -o ${NAME} ${FLAGS_PROJECT}

clean :
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY: all fclean clean re
