#include "minishell.h"

void    print_error(t_data *data)
{
    int i;

    i = 0;
    data->trace = 0;
    while (data->line[i])
    {
        if (data->line[i] != '\0' && ft_strcmp2(data->line , "echo", i) == 0 &&
            ft_strcmp2(data->line , "cd", i) == 0 && ft_strcmp2(data->line , "pwd", i) == 0 &&
                ft_strcmp2(data->line , "env", i) == 0 &&   data->trace == 0)
        {
                while (data->line[i] && (data->line[i] != ' ' && ft_verif_symbols(data->line[i]) == 0 ))
                    ft_putchar(data->line[i++]);
                write(1, ": command not found\n", 20);
                data->trace++;
        }
        if (ft_verif_symbols(data->line[i]) == 1)
        {
            while (data->line[i] == ' ' || ft_verif_symbols(data->line[i]) == 1)
                i++;
            if (data->line[i] != '\0' && ft_strcmp2(data->line , "echo", i) == 0 &&
            ft_strcmp2(data->line , "cd", i) == 0 && ft_strcmp2(data->line , "pwd", i) == 0 &&
                ft_strcmp2(data->line , "env", i) == 0)
            {
                while (data->line[i] && (data->line[i] != ' ' && ft_verif_symbols(data->line[i]) == 0 ))
                    ft_putchar(data->line[i++]);
                write(1, ": command not found\n", 20);
            }
        }
        i++;
    }
}

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
    else if (command_terminal(data) == 1)
        return (1);
    return (0);
}

char    *ft_command(t_data *data)
{
    int verif;

    init_data_parsing(data);
    malloc_parsing(data);
    ft_parsing_space(data);
    ft_parsing_firstword(data);
    if (data->parsing[data->parsing_y] == NULL)
    {
        if (ft_start(data) == 0)
            print_error(data);
    }
    else
    {
        verif = ft_parsing_following(data);
        if (verif == -1)
            return (NULL);
        if (ft_start(data) == 0)
            print_error(data);
    }
    
    for (int y = 0; y < 5; y++)
    	printf("===%s===\n", data->parsing[y]);
    return (NULL);
}