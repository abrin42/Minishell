#include "minishell.h"

void    ft_echo(char *str, int i)
{
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

void    ft_check(char *str)
{
    int i;

    i = 0;
    if (str[0] == 'e' && str[1] == 'c' && str[2] == 'h' && str[3] == 'o')
    {
        i = 5;
        ft_echo(str, i);
    }
    return ;
}

char    *ft_command(char *str)
{
    int i;
    int j;
    char    *line;

    line = malloc(sizeof(char) * 1000);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == ' ' && str[i - 1] != ' ' )
        {
            line[j] = str[i];
            j++;
            i++;
        }
        else if (str[i] == ' ' && str[i - 1] == ' ')
            i++;
        else
        {
            line[j] = str[i];
            j++;
            i++;
        }
    }
    line[j] = '\0';
    ft_check(line);
    //EN ATTENTE
    return (NULL);
}
