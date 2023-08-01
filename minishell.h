#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "gc/gc.h"

typedef struct s_data
{
    char *buffer;
    char **token;
    char **path_bdd;
    char **env;
    char **export;
    char **export_var;
    char **args;
    char *path;

    int token_i;
    int token_x;
    int token_y;
    int count_path;
    int count_pipe;
    int simple_quote;
    int double_quote;
    int i_buffer;
    int i_new_line;
    int i_var;
    int condition;
    int tube[2];

    t_gcan  gc;
}   t_data;

/***********BUILTINS***********/
void    ft_echo(t_data *data);
void    ft_pwd(t_data *data);
void    ft_cd(t_data *data);
void    ft_env(t_data *data);
void    ft_export(t_data *data);
void    ft_unset(t_data *data);
void    ft_exit(t_data *data);

/***********FUNCTION***********/
void ft_putchar(char c);
void ft_putstr(char *str);
unsigned int ft_strlen(char *str);
int ft_is_operator(char c);
int	ft_iswhitespace(char c);
char    *ft_strjoin(char *s1, char *s2, t_data *data);
int	ft_strcmp(char *s1, char *s2);
int	ft_strcmp_export_var(char *s1, char *s2);

/***********FUNCTION-MALLOC***********/
void malloc_data(t_data *data);
void malloc_path_bdd(t_data *data);
void malloc_args(t_data *data);
void    init_export_var(t_data *data);
void init_args(t_data *data);
int count_path(char *path_temp);

/***********CLEAN***********/
char *clean_buffer(t_data *data);
void    clean_var(t_data *data, char *new_line);
void    clean_token(t_data *data);
void fill_token(t_data *data);
void count_pipe(t_data *data);

/***********COMMAND***********/
void    start_command(t_data *data);
int command_exist(t_data *data);
void    execute_bultins(t_data *data);
void    execute_command (t_data *data);
void first_command_pipe(t_data *data);
void command_pipe(t_data *data);
void last_command_pipe(t_data *data);

#endif