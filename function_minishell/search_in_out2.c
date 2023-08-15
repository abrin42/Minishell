/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_out2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:58:07 by tmarie            #+#    #+#             */
/*   Updated: 2023/08/15 03:58:08 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_buffer_sio(t_data *data)
{
	int	i;

	i = 0;
	while (data->buffer_sio[i] != '\0')
	{
		data->buffer_sio[i] = '\0';
		i++;
	}
}

int	check_in_out(t_data *data)
{
	if (!data->token[data->token_y + 2][0])
	{
		printf("syntax error near unexpected token `newline'\n");
		data->error = 2;
		return (-1);
	}
	return (0);
}

int	promt_in_out_init(t_data *data, ssize_t bytes_read)
{
	g_condition_error = 43;
	clear_buffer_sio(data);
	bytes_read = read(STDIN_FILENO, data->buffer_sio, sizeof
			(data->buffer_sio));
	return (bytes_read);
}
