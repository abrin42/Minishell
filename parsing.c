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

int ft_strcmp_var(char *var, char *export_var, t_data *data)
{
    data->i_var = 0;
    
    while (export_var[data->i_var] == var[data->i_var])
        data->i_var++;
    if (export_var[data->i_var] == '=' && var[data->i_var] == '\0')
        return (-2);
    else
        return (-1);
}

void    change_by_var(t_data *data, char *new_line, int k)
{
    data->i_var = 0;
    while (data->export_var[k][data->i_var] != '\'' && data->export_var[k][data->i_var] != '"')
        data->i_var++;
    data->i_var++;
    while (data->export_var[k][data->i_var] != '\'' && data->export_var[k][data->i_var] != '"')
    {
        new_line[data->i_new_line++] = data->export_var[k][data->i_var++];
    }
    while (data->buffer[data->i_buffer] != '\0' && data->buffer[data->i_buffer] != ' ' && data->buffer[data->i_buffer] != '"')
    {
        new_line[data->i_new_line++] = ' ';
        data->i_buffer++;
    }
}

void    clear_quote(t_data *data)
{
    int i;

    i = 0;
    data->simple_quote = 0;
    data->double_quote = 0;
    while (data->buffer[i])
    {
        if (data->buffer[i] == '\'')
            data->simple_quote ++;
        else if (data->buffer[i] == '\"')
            data->double_quote++;
        i++;
    }
}

void    clean_var(t_data *data, char *new_line)
{
    char    *var;
    int     k;
    int     condition;

    var = ft_strdup_var(data->buffer, data->i_buffer + 1);
    k = 0;
    condition = 0;
    while (data->export_var[k])
    {
        if (ft_strcmp_var(var, data->export_var[k], data) == -2)
        {
            condition = -2;
            break ;
        }
        k++;
    }
    if (condition == -2)
        change_by_var(data, new_line, k);
    else
    {
        while (data->buffer[data->i_buffer] != ' ' && data->buffer[data->i_buffer] != '\0')
        {
            new_line[data->i_new_line++] = ' ';
            data->i_buffer++;
        }
    }
}