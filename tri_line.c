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

void    tri_line(t_data *data)
{
    int i;

    data->parsing = malloc (sizeof(char *) * 1000);
    data->parsing[0] = malloc (sizeof(char) * 1000);
    i = 0;
   // printf("-okkkkk-\n");
    while (data->line[i] != '\0')
    {
        //printf("-line:%s-\n",data->line);
	if (ft_check(data->line) == 1)
        {
            data->parsing[data->parsing_y] = "echo";
        }
        data->line++;
        i++;
    }
    printf("-parssing[0]%s-\n",data->parsing[0]);
}
