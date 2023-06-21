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
    else if (ft_strcmp(data->parsing[0] , "ls") == 0)
    {
        ft_terminal(data);
        return (1);
    }
    return (0);
}

void    doublecot(t_data *data)
{
    int i;

    i = 0;
    data->line++;
    while(data->line[data->lenquote] && data->line[data->lenquote] != '"')
    {          
        data->lenquote++;
    }
    while (data->lenquote > i)
    {
        data->parsing[data->parsing_y][i] = data->line[i];
        i++;
    }
    data->line += data->lenquote + 1;
    printf("-parssingavant[1]%s-\n",data->parsing[1]);
}


/*int    ft_check(t_data *data, int u)
{
    int i;
    if (data->line[u] == '>')
    {
        printf("---------------------------\n");
        data->parsing[data->parsing_y][0] = data->line[u++];
        data->parsing_y++;
        return (1);
    }
    i = 0;
    return(0);
}*/

char    *ft_command(t_data *data)
{
    ft_parsing_lineset(data);
    ft_parsing_tri_line(data);
    ft_start(data);
    return (NULL);
}