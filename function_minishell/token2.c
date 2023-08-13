/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 05:59:08 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 05:59:09 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_token(t_data *data)
{
	int	i;
	int	y;

	data->token_y = 0;
	i = 0;
	while (i < 100)
	{
		data->token[i++][0] = '\0';
	}
}

int	fill_token_quote_condition1(t_data *data, int i)
{
	while (data->buffer[i] != '\'')
		data->token[data->token_y][data->token_x++] = data->buffer[i++];
	data->token[data->token_y][data->token_x] = '\0';
	i++;
	return (i);
}
