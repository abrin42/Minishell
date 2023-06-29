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

void    test_comande_possible(t_data * data)
{
    if (ft_strcmp(data->parsing[data->parsing_y] , "echo") == 0)
        return (1);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "cd") == 0)
        return (1);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "pwd") == 0)
        return (1);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "env") == 0)
        return (1);
    else (command_terminal(data) == 1) // change command_terminal sans execution (commande access)
        return (1);
    return (0);
}

void    execute(t_data *data)
{
    if (ft_strcmp(data->parsing[data->parsing_y] , "echo") == 0)
        ft_echo(data, 5);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "cd") == 0)
        ft_cd(data);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "pwd") == 0)
        ft_pwd(data);
    else if (ft_strcmp(data->parsing[data->parsing_y] , "env") == 0)
        ft_env(data);
    else if(!command_terminal(data) == 1)
        return (0);
    return (1);
}