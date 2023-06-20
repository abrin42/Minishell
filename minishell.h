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
}   t_data;

char    *ft_command(t_data *data);
int    ft_parsing_signe(t_data *data, int u);
int ft_strlen(char  *str);
int	ft_strcmp(char *s1, char *s2);
void    ft_parsing_tri_line(t_data *data);
void    ft_echo(t_data *data, int i);
void    ft_pwd(t_data *data);
void    ft_cd(t_data *data);
void    ft_env(t_data *data);
void    ft_terminal(t_data *data);
void    ft_parsing_lineset(t_data *data);

#endif
