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
	char	*str_join;
	char	*path_temp;
	char	*buf;
	char	buffer_sio[2048];
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
	int		i_bdd;
	int		x_bdd;
	int		y_bdd;
	int		count_bdd;
	int		x;
	int		p;
	int		i;
	int		k;
	int		count_pipe2;
	int		count_redirect;
	int		quote_fake;
	int		echo_n;
	int		trace_echo;
	int		i_echo;
	t_gcan	gc;
	size_t	i_join;
	size_t	c_join;
}	t_data;

/***********MAIN***********************************/
/*minishell_annexe.c*/
void		init_data(t_data *data);
void		handle_signal(int i);
int			test_pipe_end(t_data *data);
int			prompt3(t_data *data);
void		prompt2(t_data *data);
/**/
/*minishell.c*/
void		prompt(t_data *data);
int			main(int argc, char **argv, char **envp);
/**/
/*other.c*/
void		other_prompt2(t_data *data);
/**/
/***********BUILTINS***************************/
/*builtins.c*/
void		ft_echo(t_data *data);
void		ft_pwd(t_data *data);
void		ft_cd(t_data *data);
void		ft_env(t_data *data);
void		ft_exit(t_data *data);
/**/
/*builtins2.c*/
void		ft_echo_n(t_data *data);
void		ft_unset(t_data *data);
/**/
/*builtins3.c*/
void		ft_echo_n1(t_data *data);
void		ft_echo_n2(t_data *data);
void		ft_echo_n_init(t_data *data);
int			ft_echo_n_if(t_data *data);
int			ft_echo_n_if2(t_data *data);
/**/
/*builtin_export.c*/
void		clean_result_export_var(t_data *data, int i);
void		tri_export(t_data *data);
void		tri_export_var(t_data *data);
void		ft_export2(t_data *data, int i);
void		ft_export(t_data *data);
/**/
/*builtin_export2.c*/
void		init_export_var(t_data *data);
int			ft_strcmp_export_var(char *s1, char *s2);
void		reset_var(char *str);
int			ft_strcmp_unset(char *s1, char *s2);
/**/
/*builtin_export3.c*/
char		*ft_strdup_special(const char *src);
void		clean_result_export_var2(t_data *data, int i, int y);
/**/
/***********UTILS***************************/
/*function.c*/
void		ft_putchar(char c);
void		ft_putstr(char *str);
int			ft_strlen(char *str);
int			ft_is_operator(char c);
int			ft_iswhitespace(char c);
/**/
/*function2.c*/
void		ft_putstr_error(t_data *data, char *str);
char		*ft_strjoin2(char *s1, char *s2, t_data *data);
char		*ft_strjoin(char *s1, char *s2, t_data *data);
char		*ft_strjoin3(char *s1, char *s2, t_data *data, int p);
int			ft_strcmp(char *s1, char *s2);
/**/
/*function3.c*/
int			ft_isalpha_str(char *str);
int			ft_isprint(int c);
/**/
/*function4.c*/
int			ft_strcmp3(char *s1, char *s2);
int			ft_strcmp2(char *s1, char *s2);
void		init_args(t_data *data);
int			ft_atoi(const char *nptr);
/**/
/*function_malloc.c*/
int			count_path(char *path_temp);
void		malloc_path_bdd1(t_data *data);
int			malloc_path_bdd(t_data *data);
void		malloc_data(t_data *data);
void		malloc_args(t_data *data);
/**/
/*function_malloc2.c*/
void		ft_getenv_path(t_data *data);
void		ft_get_path(t_data *data, int i);
/**/
/***********TOKEN****************************/
/*token.c*/
void		advance_fill_token_operator(t_data *data);
void		fill_token3(t_data *data);
void		fill_token2(t_data *data);
void		init_data_token(t_data *data);
void		fill_token(t_data *data);
/**/
/*token2.c*/
void		clean_token(t_data *data);
int			fill_token_quote_condition1(t_data *data, int i);
int			token_quote_empty(t_data *data, int i);
/**/
/*token_quote.c*/
void		fill_token_quote_condition(t_data *data, int i);
void		fill_token_quote_new_line(t_data *data);
void		clear_quote(t_data *data, char c);
char		*ft_parsing_space_quote(t_data *data);
int			fill_token_quote(t_data *data, int i);
/**/
/***********CLEAN********************************/
/*clean_buffer.c*/
void		clean_buffer2(t_data *data);
void		clean_buffer1(t_data *data);
void		init_clean_buffer(t_data *data);
char		*clean_buffer(t_data *data);
/**/
/*clean_buffer2.c*/
void		clean_buffer5(t_data *data);
void		clean_buffer4(t_data *data);
void		clean_buffer3(t_data *data);
/**/
/*count_init.c*/
int			check_bin(t_data *data);
void		count_pipe_redirect(t_data *data);
void		init_count_pipe_redirect(t_data *data);
void		count_pipe(t_data *data);
/**/
/*clean_variable_export.c*/
char		*ft_strdup_var(const char *src, int i, t_data *data);
int			ft_strcmp_var(char *var, char *export_var, t_data *data);
void		change_by_var(t_data *data, char *new_line, int k);
void		clean_var(t_data *data, char *new_line);
/**/
/***********COMMAND****************************/
/*start_command.c*/
void		execute_bultins(t_data *data);
void		execute_command(t_data *data);
void		execute(t_data *data);
void		execute_cmd(t_data *data, int fd_pipe);
void		start_command(t_data *data);
/**/
/*command_pos.c*/
void		execute_cmd_start1(t_data *data, int *pipe_in);
void		execute_cmd_middle1(t_data *data, int *pipe_in, int *fd_pipe);
void		execute_cmd_end1(t_data *data, int *pipe_in, int *fd_pipe);
/**/
/*command_exist.c*/
void		cmd_solo(t_data *data);
void		error_127(t_data *data);
int			command_exist_builtin(t_data *data);
int			command_exist(t_data *data);
/**/
/***********COMMAND-REDIR**********************/
/*redir.c*/
void		execute_redirect(t_data *data, int y);
int			command_exist_redirect2(t_data *data, int y);
void		execute_in_file(t_data *data, int y);
int			check_redirect(t_data *data);
int			check_redirect_inverse(t_data *data);
/**/
/*redir_in_file_pipe*/
void		execute_in_file_first_pipe(t_data *data, int y, int *fd_pipe);
int			check_redirect_pipe(t_data *data);
void		execute_in_file_pipe3(t_data *data, int y, int *fd_pipe, int fd);
void		execute_in_file_pipe2(t_data *data, int *fd_pipe);
void		execute_in_file_pipe(t_data *data, int y, int *fd_pipe);
/**/
/*redir_in_file*/
void		init_args_redirect(t_data *data, int x);
int			command_exist_redirect(t_data *data, int y);
void		execute_in_file_pipe_open(t_data *data);
void		redirection_in_file(t_data *data, int y);
void		execute_command_redirect(t_data *data, int y);
/**/
/***********COMMAND-SEARCH****************************/
/*redir_serch.c*/
void		execute_search(t_data *data);
void		search_in_file_error(t_data *data);
void		init_search_in_file(t_data *data);
void		search_in_file1(t_data *data);
int			search_in_file(t_data *data, int y);
/**/
/*redir_search_start.c*/
void		execute_search_pipe_start3(t_data *data, int *fd_pipe);
void		execute_search_pipe_start2(t_data *data, int *fd_pipe);
void		execute_search_pipe_start(t_data *data, int *fd_pipe);
/**/
/*redir_search_pipe.c*/
void		execute_search_pipe_void(t_data *data, int *fd_pipe);
void		execute_search_pipe_middle1(t_data *data, int *fd_in, int *fd_out);
void		execute_search_pipe_middle(t_data *data, int *fd_in, int *fd_out);
void		execute_search_pipe_end(t_data *data, int *fd_pipe);
/**/
/***********COMMAND-SEARCH-IN-OUT****************************/
/*search_in_out.c*/
int			check_in_out(t_data *data);
void		clear_buffer_sio(t_data *data);
void		promt_in_out(t_data *data, int *pipe_sio, ssize_t bytes_read);
void		dup2_search_in_out(t_data *data, int *pipe_sio);
void		execute_command_search_in_out(t_data *data);
/**/

/*search_in_out_pipe.c*/
void		execute_search_in_pipe(t_data *data, int *fd_pipe);
void		execute_search_in_pipe_end(t_data *data, int *fd_pipe);
void		error_search_in_pipe(t_data *data);
void		dup2_search_in_pipe(t_data	*data, int *pipe_sio, int *fd_pipe);
void		search_in_avance(t_data *data);
/**/
/*search_in_out_pipe2.c*/
void		search_in_pipe_close(t_data *data, int *pipe_sio, int *fd_pipe);
void		dup2_search_in_pipe_end(t_data *data, int *pipe_sio, int *fd_pipe);
void		check_error(t_data *data);
/**/
/***********COMMAND-PIPE**************************/
/*pipe.c*/
void		pipe_start(t_data *data, int *fd_pipe);
void		pipe_middle(t_data *data, int *fd_pipe_in, int *fd_pipe_out);
void		pipe_end(t_data *data, int *fd_pipe);
void		pipe_avance(t_data *data);
/**/
/************************************************/

#endif
