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
    else if (command_terminal(data))
        return (1);
    return (0);
}

char    *ft_command(t_data *data)
{
    init_data_parsing(data);
    malloc_parsing(data);
    ft_parsing_space(data);
    ft_parsing_firstword(data);
    if (data->parsing[data->parsing_y] == NULL)
        ft_start(data);
    else
    {
        ft_parsing_following(data);
        ft_start(data);
    }
    return (NULL);
}

