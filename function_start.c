/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:29:14 by abrin             #+#    #+#             */
/*   Updated: 2023/06/27 19:29:16 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cmd_possible(t_data *data)
{
    //char **args;
    char *path;
    int i;
    int stop_condition;
    int status;

    //args = malloc_args(data, args);
    malloc_bdd(data);
    i = 0;
    while (data->bdd[i] != NULL )
    {
        stop_condition = 0;
        path = ft_strjoin(data->bdd[i], data->parsing[data->parsing_y]); //attention data->parsing[0] echo | ls = ls
        if (access(path, X_OK) == 0)
            return(0);
        free(path);
        i++;
    }
    return(-1);
}

int    test_comande_possible(t_data *data)
{
    if (ft_strcmp(data->parsing[data->parsing_y] , "echo") == 0)
        return (1);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "cd") == 0)
        return (1);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "pwd") == 0)
        return (1);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "env") == 0)
        return (1);
    else if (cmd_possible(data) == 0) // change command_terminal sans execution (commande access)
        return (1);
    printf("test comande ligne [%d] = %s \n",data->parsing_y,data->parsing[data->parsing_y]);
    return (0);
}

void    execute(t_data *data)
{
    int i = 1;
    if (ft_strcmp(data->parsing[data->parsing_y] , "echo") == 0)
        ft_echo(data, 5);
     if (ft_strcmp(data->parsing[data->parsing_y] , "cd") == 0)
        ft_cd(data);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "pwd") == 0)
        ft_pwd(data);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "env") == 0)
        ft_env(data);
    else if(command_terminal(data) == 1)
        i = i;
}