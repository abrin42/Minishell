#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
    char    *buf;

} t_data;


char    *ft_command(char *str);
void    ft_check(char *str);
void    ft_echo(char *str, int i);
int ft_strlen(char  *str);

#endif