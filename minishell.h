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
    int     parsing_y;
    int     lenquote;
    int     i_args;
    int     i_line;
    int     u_line;
    int     comd_line;
    int     malloc_pars;
    int     trace;
}   t_data;

char    *ft_command(t_data *data);
int     ft_start(t_data *data);

int    ft_parsing_following(t_data *data);
void    ft_parsing_firstword(t_data *data);
void    ft_parsing_space(t_data *data);

void    ft_echo(t_data *data, int i);
void    ft_pwd(t_data *data);
void    ft_cd(t_data *data);
void    ft_env(t_data *data);
int     command_terminal (t_data *data);

char    *ft_strjoin(char *s1, char *s2);
int     ft_strlen(char  *str);
int	    ft_strcmp(char *s1, char *s2);
int	    ft_strcmp2(char *s1, char *s2, int start);
void    ft_putchar(char c);



void    malloc_bdd(t_data *data);
void    malloc_parsing(t_data *data);
void    malloc_parsing(t_data *data);
char    **malloc_args(t_data *data, char **args);
void    init_data(t_data *data, char **envp);
void    init_data_parsing(t_data *data);
void    free_args(char **args, t_data *data);
void    ft_split_path(t_data *data);
int    ft_verif_symbols(char c);

#endif
