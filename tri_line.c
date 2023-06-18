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

void    init_bdd(t_data *data)
{
    data->bdd = malloc(sizeof(char *) * 7);

    data->bdd[0] = "echo";
    data->bdd[1] = "cd";
    data->bdd[2] = "pwd";
    data->bdd[3] = "export";
    data->bdd[4] = "unset";
    data->bdd[5] = "env";
    data->bdd[6] = "exit";
}

void    tri_line(t_data *data)
{
    int i;
    int u;

    data->parsing = malloc (sizeof(char *) * 1000);
    data->parsing[0] = malloc (sizeof(char) * 1000);
    data->parsing[1] = malloc (sizeof(char) * 1000);
    i = 0;
   // printf("-okkkkk-\n");
    data->parsing_y = 0;
    while (data->line[i] != '\0')
    {
        u = 0;
        //printf("-line:%s-\n",data->line);
        if (ft_check(data->line) == 1)
        {
            data->parsing[data->parsing_y] = "echo";
            data->parsing_y++;
            data->line += 5;
            while (data->line[u] && ft_check(data->line) == 0)
                data->parsing[data->parsing_y][u++] = data->line[u];
            data->parsing_y++;
        }
        else if (ft_check(data->line) == 2)
        {
            data->parsing[data->parsing_y] = "cd";
            data->parsing_y++;
        }
        else if (ft_check(data->line) == 3)
        {
            data->parsing[data->parsing_y] = "pwd";
            data->parsing_y++;
        }
        else if (ft_check(data->line) == 6)
        {
            data->parsing[data->parsing_y] = "env";
            data->parsing_y++;
        }
        data->line++;
        i++;

    }
    //data->parsing[data->parsing_y] = data->line;
    printf("-parssing[0]%s-\n",data->parsing[0]);
    printf("-parssing[1]%s-\n",data->parsing[1]);
    printf("-line:%s-\n",data->line);

}
