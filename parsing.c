/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:30:28 by abrin             #+#    #+#             */
/*   Updated: 2023/06/17 18:30:30 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_parsing_lineset(t_data *data)
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
    data->line[j] = '\0';
}

int    ft_parsing_signe(t_data *data)
{
    int i;
    if (data->line[data->u_line] == '>' || data->line[data->u_line] == '<' || data->line[data->u_line] == '|')
    {
        data->parsing_y++;
        data->parsing[data->parsing_y][0] = data->line[data->u_line];
        data->u_line++;
        data->u_line++;
        return (1);
    }
    i = 0;
    return(0);
}