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

SRC	=	main.c			\
		function.c		\
		command.c		\
		ft_command.c 	\
		parsing.c		\
		parsing2.c		\
		verif_command.c \
		function_start.c

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
