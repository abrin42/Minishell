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

void    malloc_parsing(t_data *data)
{
    data->i_args = 1000;
    data->parsing = malloc (sizeof(char *) * data->i_args);
    while (data->i_args >= 0)
    {
        data->parsing[data->i_args] = malloc (sizeof(char) * 1000);
        //data->parsing[data->i_args] = NULL;
        data->i_args--;
    }
}

void    ft_parsing_tri_line(t_data *data)
{
    int i;

    /*data->parsing = malloc (sizeof(char *) * 1000);
    data->parsing[0] = malloc (sizeof(char) * 1000);
    data->parsing[1] = malloc (sizeof(char) * 1000);
    data->parsing[2] = malloc (sizeof(char) * 1000);
    data->parsing[3] = malloc (sizeof(char) * 1000);
    data->parsing[4] = malloc (sizeof(char) * 1000);
    data->parsing[5] = malloc (sizeof(char) * 1000);
    data->parsing[6] = malloc (sizeof(char) * 1000);*/
    malloc_parsing(data);

   // printf("-okkkkk-\n");
    data->parsing_y = -1;
    data->u_line = 0;
    data->comd_line = 1;
    while (data->line[data->u_line])
    {
        i = 0;
        data->parsing_y++;
        printf("data->parsing_y :%d\n",data->parsing_y);
        printf("line u{%c}\n",data->line[data->u_line]);
        while ((data->line[data->u_line] && data->line[data->u_line] != ' ') /*|| data->line[data->u_line-1] != ' ' */)
        {
            data->parsing[data->parsing_y][i++] = data->line[data->u_line++];
        }
        data->parsing_y++;
        i = 0;
        data->u_line++;
        data->comd_line = 0;
        while (data->line[data->u_line] && ft_parsing_signe(data) == 0)
        {
            data->parsing[data->parsing_y][i++] = data->line[data->u_line++];
        }
    }
    data->parsing_y -= data->trace;
    printf("%d\n", data->parsing_y);
    while (data->parsing_y < 1000)
    {
        data->parsing_y++;
        data->parsing[data->parsing_y] = NULL;
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
    printf("-parssing[4]%s-\n",data->parsing[4]);
    printf("-parssing[5]%s-\n",data->parsing[5]);
    printf("-parssing[6]%s-\n",data->parsing[6]);
    printf("-line:%s-\n",data->line);

}
