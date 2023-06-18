#include "minishell.h"

int    ft_start(t_data *data)
{
     int i;

    i = 0;
    if (data->parsing[0] == "echo")
    {
        i = 5;
        ft_echo(data, i);
        return (1);
    }
    else if (data->parsing[0] == "pwd")
    {
        ft_pwd(data);
    }
    return (0);
}


int    ft_check(char *str)
{
    int i;

    i = 0;
    //printf("-str:%s-\n",str);
    if (str[0] == 'e' && str[1] == 'c' && str[2] == 'h' && str[3] == 'o')
        return (1);
    else if (str[0] == 'p' && str[1] == 'w' && str[2] == 'd')
        return (2);
    return (0);
}

char    *ft_command(t_data *data)
{
    int i;
    int j;

    data->line = malloc(sizeof(char) * 1000);
    i = 0;
    j = 0;
    while (data->buffer[i])
    {
    if (data->buffer[i] == ' ' && data->buffer[i - 1] == ' ')
            i++;
        else
        {
            data->line[j] = data->buffer[i];
            j++;
            i++;
        }
    }
    tri_line(data);
   // printf("-line:%s-\n",data->line);
    data->line[j] = '\0';
    ft_start(data);
    //EN ATTENTE
    return (NULL);
}