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

    //*tab = malloc (sizeof(char) *1000);
    i = 0;
   // printf("-okkkkk-\n");
    while (data->line[i] != '\0')
    {
      //  printf("-line:%s-\n",data->line);
        if (1 == ft_check(data->line));
        //    tab[data->tab_y];
        data->line++;
        i++;
    }
}
