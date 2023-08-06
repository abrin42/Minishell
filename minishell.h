/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:35:25 by abrin             #+#    #+#             */
/*   Updated: 2023/08/06 19:35:26 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "gc/gc.h"
# include <errno.h>

typedef struct s_data
{
	char	*buffer;
	char	**token;
	char	**path_bdd;
	char	**env;
	char	**export;
	char	**export_var;
	char	**args;
	char	*path;
	char	*buf;
	char	*new_line;
	char	*var;
	char	*save;
	int		token_i;
	int		token_x;
	int		token_y;
	int		count_path;
	int		count_pipe;
	int		simple_quote;
	int		double_quote;
	int		i_buffer;
	int		i_new_line;
	int		i_var;
	int		condition;
	int		add;
	int		token_txt;
	int		tube_redirect[2];
	int		tube_search[2];
	int		pipe_not_close;
	int		buf_str;
	int		error;
	int		condition1;
	int		condition2;
	int		fd;
	int		fd1;
	int		x;
	int		p;
	int		i;
	int		k;
	int		count_pipe2;
	int		count_redirect;
	t_gcan	gc;
}	t_data;

/***********BUILTINS***********/
void			ft_echo(t_data *data);
void			ft_pwd(t_data *data);
void			ft_cd(t_data *data);
void			ft_env(t_data *data);
void			ft_export(t_data *data);
void			ft_unset(t_data *data);
void			ft_exit(t_data *data);

/***********FUNCTION***********/
void			ft_putchar(char c);
void			ft_putstr(char *str);
void			ft_putstr_error(t_data *data, char *str);
unsigned int	ft_strlen(char *str);
int				ft_is_operator(char c);
int				ft_iswhitespace(char c);
char			*ft_strjoin(char *s1, char *s2, t_data *data);
char			*ft_strjoin2(char *s1, char *s2, t_data *data);
char			*ft_strjoin3(char *s1, char *s2, t_data *data, int p);
int				ft_strcmp(char *s1, char *s2);
int				ft_strcmp2(char *s1, char *s2);
int				ft_strcmp_export_var(char *s1, char *s2);

/***********FUNCTION-MALLOC***********/
void			malloc_data(t_data *data);
void			malloc_path_bdd(t_data *data);
void			malloc_args(t_data *data);
void			init_export_var(t_data *data);
void			init_args(t_data *data);
int				count_path(char *path_temp);

/***********CLEAN***********/
char			*clean_buffer(t_data *data);
void			clean_var(t_data *data, char *new_line);
void			clean_token(t_data *data);
void			fill_token(t_data *data);
void			count_pipe(t_data *data);
void			error_open_search(t_data *data, int fd);

/***********COMMAND***********/
void			start_command(t_data *data);
int				command_exist(t_data *data);
void			execute_bultins(t_data *data);
void			execute_command(t_data *data);
void			execute_cmd(t_data *data, int fd_pipe);
void			execute(t_data *data);
void			pipe_start(t_data *data, int *fd_pipe);
void			pipe_middle(t_data *data, int *fd_pipe_in, int *fd_pipe_out);
void			pipe_end(t_data *data, int *fd_pipe);
void			execute_in_file(t_data *data, int y);
void			execute_in_file_pipe(t_data *data, int y, int *fd_pipe);
void			execute_in_file_first_pipe(t_data *data, int y, int *fd_pipe);
int				check_redirect(t_data *data);
int				check_redirect_pipe(t_data *data);
int				command_exist_redirect(t_data *data, int y);
void			execute_command_redirect(t_data *data, int y);

int				search_in_file(t_data *data, int y);
int				check_redirect_inverse(t_data *data);
void			execute_search(t_data *data);

void			execute_search_pipe_start(t_data *data, int *fd_pipe);
void			execute_search_pipe_middle(t_data *data, int *fd_in, int *fd_out);
void			execute_search_pipe_end(t_data *data, int *fd_pipe);
void			execute_search_pipe_void(t_data *data, int *fd_pipe);

#endif
