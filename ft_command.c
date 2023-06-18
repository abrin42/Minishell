#include "minishell.h"

int    ft_start(t_data *data)
{
     int i;

    i = 0;
    if (ft_strcmp(data->parsing[0] , "echo") == 0)
    {
        i = 5;
        ft_echo(data, i);
        return (1);
    }
    else if (ft_strcmp(data->parsing[0] , "cd") == 0)
    {
        ft_cd(data);
        return (1);
    }
    else if (ft_strcmp(data->parsing[0] , "pwd") == 0)
    {
        ft_pwd(data);
        return (1);
    }
    else if (ft_strcmp(data->parsing[0] , "env") == 0)
    {
        ft_env(data);
        return (1);
    }
    return (0);
}


int    ft_check(t_data *data)
{
    int i;

    i = 0;
    //printf("-str:%s-\n",str);
    if (data->line[0] == 'e' && data->line[1] == 'c' && data->line[2] == 'h' && data->line[3] == 'o')
    {
        data->parsing[data->parsing_y] = "echo";
        data->line += 5;
        return (1);
    }
    else if (data->line[0] == 'c' && data->line[1] == 'd')
    {
        data->parsing[data->parsing_y] = "cd";
        data->line += 3;
        return (2);
    }
    else if (data->line[0] == 'p' && data->line[1] == 'w' && data->line[2] == 'd')
    {
        data->parsing[data->parsing_y] = "pwd";
        data->line += 4;
        return (3);
    }
    else if (data->line[0] == 'e' && data->line[1] == 'n' && data->line[2] == 'v')
    {
        data->parsing[data->parsing_y] = "env";
        data->line += 4;
        return (6);
    }
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
    //printf("-line:%s-\n",data->line);
    data->line[j] = '\0';
    ft_start(data);
    //EN ATTENTE
    return (NULL);
}