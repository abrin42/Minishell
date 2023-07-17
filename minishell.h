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

typedef struct s_data
{
    char    *buffer;
    char    *line;
    char    **parsing;
    char    **bdd;
    char    **env;
    char    **export;
    char    **export_var;
    int     parsing_y;
    int     lenquote;
    int     i_args;
    int     i_line;
    int     u_line;
    int     comd_line;
    int     malloc_pars;
    int     trace;
    int     i_buffer;
    int     i_new_line;
    int     i_var;
    int     simple_quote;
    int     double_quote;    
    
    int tube_1[2];
    int tube_2[2];
    int tube_trace;
}   t_data;

int    ft_command(t_data *data);
int     ft_start(t_data *data);
int    test_comande_possible(t_data *data);


int    ft_parsing_following(t_data *data);
void    ft_parsing_firstword(t_data *data);
void    ft_parsing_space(t_data *data);

void    ft_echo(t_data *data, int i);
void    ft_pwd(t_data *data);
void    ft_cd(t_data *data);
void    ft_env(t_data *data);
void    ft_export(t_data *data);
void    ft_unset(t_data *data);
int     command_terminal (t_data *data);
void    execute(t_data *data);

char    *ft_strjoin(char *s1, char *s2);
int     ft_strlen(char  *str);
int	    ft_strcmp(char *s1, char *s2);
int	    ft_strcmp2(char *s1, char *s2, int start);
void    ft_putchar(char c);
char	*ft_strdup(const char *s);
void    ft_putstr(char *str);
char	*ft_strcpy(char *dst, char *src);
char	*ft_strdup_size(const char *s, int size,int  start);
char	*ft_strdup_var(const char *src, int i);
char	*ft_strdup_special(const char *src);


void    prompt(t_data *data);


void    malloc_bdd(t_data *data);
void    malloc_parsing(t_data *data);
void    malloc_parsing(t_data *data);
char    **malloc_args(t_data *data, char **args, char *path);
void    init_data(t_data *data, char **envp);
void    init_data_parsing(t_data *data);
void    init_export_var(t_data *data);
void    free_args(char **args, t_data *data);
void    ft_split_path(t_data *data);
int    ft_verif_symbols(char c);
void    clean_var(t_data *data, char *new_line);
void    clear_quote(t_data *data);
void    change_by_var(t_data *data, char *new_line, int k);
int     ft_strcmp_var(char *var, char *export_var, t_data *data);

#endif
