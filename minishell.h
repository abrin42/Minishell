#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
    char    *buffer;
    char    *line;
    char    *pwd;
    char    **parsing;
    char    **test;
    char    **bdd;
    char    **env;
    int     parsing_y;
}   t_data;

char    *ft_command(t_data *data);
int    ft_check(char *str);
int ft_strlen(char  *str);
int	ft_strcmp(char *s1, char *s2);
void    tri_line(t_data *data);
void    ft_echo(t_data *data, int i);
void    ft_pwd(t_data *data);
void    init_bdd(t_data *data);


#endif
