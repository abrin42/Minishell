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

SRC	=	minishell.c									\
		minishell_annexe.c							\
		command/start_command.c						\
		command/command_exist.c						\
		command/command_pos.c						\
		function_utils/function.c					\
		function_utils/function2.c					\
		function_utils/function_malloc.c			\
		function_utils/other.c						\
		function_minishell/clean_variable_export.c	\
		function_minishell/count_init.c				\
		function_minishell/builtins.c				\
		function_minishell/builtins2.c				\
		function_minishell/builtin_export.c			\
		function_minishell/builtin_export2.c		\
		function_minishell/builtin_export3.c		\
		function_minishell/pipe.c					\
		function_minishell/redir.c					\
		function_minishell/redir_in_file.c			\
		function_minishell/redir_in_file_pipe.c		\
		function_minishell/redir_search.c			\
		function_minishell/redir_search_pipe.c		\
		function_minishell/redir_search_start.c		\
		function_minishell/token.c					\
		function_minishell/token2.c					\
		function_minishell/token_quote.c			\
		function_minishell/clen_buffer.c			\
		function_minishell/clen_buffer2.c			\

SRC_H = minishell.h

LIBGCDIR = gc
LIBGC = libgc.a
LIBGCFLAGS = -L $(LIBGCDIR) -l:$(LIBGC)

OBJ	=	${SRC:.c=.o}

NAME	=	minishell

FLAGS	=	-Wall -Wextra -Werror

FLAGS_PROJECT = -lreadline -g

all : ${NAME}

$(LIBGCDIR)/$(LIBGC):
	make -C $(LIBGCDIR)

$(NAME) : ${OBJ} $(LIBGCDIR)/$(LIBGC)
	gcc ${FLAGS} ${OBJ} ${SRC_H} -o ${NAME} $(LIBGCFLAGS) ${FLAGS_PROJECT}

clean :
	rm -f ${OBJ}

fclean : clean
	rm -f ${NAME}
	make -C $(LIBGCDIR) fclean

re : fclean all

.PHONY: all fclean clean re
