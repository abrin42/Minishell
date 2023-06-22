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

void    ft_parsing_space(t_data *data)
{
    int i;
    int j;

    data->line = malloc(sizeof(char) * (ft_strlen(data->buffer) + 1));
    i = 0;
    j = 0;
    while (data->buffer[i] == ' ')
        i++;
    while (data->buffer[i])
    {
    if ((data->buffer[i] == ' ' && data->buffer[i + 1] == ' ') || (data->buffer[i] == ' ' && data->buffer[i + 1] == '\0'))
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

void    ft_parsing_firstword(t_data *data)
{
    int j;

    j = 0;
    while (data->line[data->i_line] == ' ')
        data->i_line++;
    while (data->i_line < ft_strlen(data->buffer) && data->line[data->i_line] != ' ')
    {
        data->parsing[data->parsing_y][j] = data->line[data->i_line];
        data->i_line++;
        j++;
    }
    data->parsing[data->parsing_y][j] = '\0';
    data->parsing_y++;
    data->i_line++;
    if (data->i_line >= ft_strlen(data->buffer))
        data->parsing[data->parsing_y] = NULL;
}

int    ft_parsing_following(t_data *data)
{
    int j;

    j = 0;
    while (data->i_line < ft_strlen(data->buffer) && ft_verif_symbols(data->line[data->i_line]) == 0)
    {
        if (data->line[data->i_line] == ' ' && ft_verif_symbols(data->line[data->i_line + 1]) == 1)
            data->i_line++;
        else
        {
            data->parsing[data->parsing_y][j] = data->line[data->i_line];
            data->i_line++;
            j++;
        }
    }
    data->parsing[data->parsing_y][j] = '\0';
    data->parsing_y++;
    j = 0;
    while (ft_verif_symbols(data->line[data->i_line]) == 1)
    {
        data->parsing[data->parsing_y][j] = data->line[data->i_line];
        j++;
        data->i_line++;
    }
    data->parsing_y++;
    if (data->parsing[data->parsing_y - 1][0] == '|' && data->parsing[data->parsing_y - 1][1] == '|')
    {
        printf("syntax error near unexpected token '%c%c'\n", data->parsing[data->parsing_y - 1][0], data->parsing[data->parsing_y - 1][0]);
        return (-1);
    }
    else if (ft_verif_symbols(data->parsing[data->parsing_y - 1][0]) == 1 && ft_verif_symbols(data->parsing[data->parsing_y - 1][1]) == 1 && ft_verif_symbols(data->parsing[data->parsing_y - 1][2]) == 1)
    {
        printf("syntax error near unexpected token '%c%c'\n", data->parsing[data->parsing_y - 1][0], data->parsing[data->parsing_y - 1][0]);
        return (-1);
    }
    if (data->i_line < ft_strlen(data->buffer))
    {
        ft_parsing_firstword(data);
        if (data->parsing[data->parsing_y] != NULL)
            ft_parsing_following(data);
    }
    while (data->parsing_y < 1000)
    {
        data->parsing[data->parsing_y] = NULL;
        data->parsing_y++;
    }
    return (0);
}