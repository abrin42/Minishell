/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 18:54:30 by abrin             #+#    #+#             */
/*   Updated: 2023/06/17 18:54:31 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_parsing_tri_line(t_data *data)
{
    int i;
    int u;

    data->parsing = malloc (sizeof(char *) * 1000);
    data->parsing[0] = malloc (sizeof(char) * 1000);
    data->parsing[1] = malloc (sizeof(char) * 1000);
    data->parsing[2] = malloc (sizeof(char) * 1000);
    data->parsing[3] = malloc (sizeof(char) * 1000);


    i = 0;
   // printf("-okkkkk-\n");
    data->parsing_y = -1;
    u = 0; 
    while (data->line[u])
    {
        i = 0;
        data->parsing_y++;
        while (data->line[u] && data->line[u] != ' ')
        {
            data->parsing[data->parsing_y][i++] = data->line[u++];
        }
        data->parsing_y++;
        i = 0;
        u++;
        while (data->line[u] && ft_parsing_signe(data, u) == 0)
        {
            data->parsing[data->parsing_y][i++] = data->line[u++];
        }
    }
    
    /*
    while (data->line[i] != '\0')
    {
        data->lenquote = 0;
        u = 0;
        if (ft_check(data) != 0)
        {
            //data->line += ft_strlen(data->parsing[data->parsing_y]) + 1;
            data->parsing_y++;
            while (data->line[u] && ft_check(data) == 1 && data->line[u] != '"')
            {
                data->parsing[data->parsing_y][u++] = data->line[u];
                printf("-parssing[1]%s-\n",data->parsing[1]+1);
            }
            //printf("-lenquote :%d-\n",data->lenquote);
            //printf("-strlen :%d-\n",ft_strlen(data->parsing[data->parsing_y]));
            data->line += ft_strlen(data->parsing[data->parsing_y]);
            data->parsing_y++;
        }
        i++;

    }*/
    //data->parsing[data->parsing_y] = data->line;
    printf("-parssing[0]%s-\n",data->parsing[0]);
    printf("-parssing[1]%s-\n",data->parsing[1]);
    printf("-parssing[2]%s-\n",data->parsing[2]);
    printf("-parssing[3]%s-\n",data->parsing[3]);
    printf("-line:%s-\n",data->line);

}
