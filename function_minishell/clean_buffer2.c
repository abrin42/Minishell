/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clen_buffer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 05:46:06 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 05:46:07 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_buffer5(t_data *data)
{
	if (data->buffer[data->i_buffer] == '\'')
		clean_buffer2(data);
	else if (data->buffer[data->i_buffer] == '"')
		clean_buffer3(data);
	else if ((data->buffer[data->i_buffer] == '$'
			&& data->buffer[data->i_buffer + 1] == '?'))
	{
		clean_buffer4(data);
		data->i_buffer++;
	}
	else if (data->buffer[data->i_buffer] == '$' && data->buffer
		[data->i_buffer + 1] != ' ' && data->buffer[data->i_buffer + 1] != '\0')
	{
		clean_var(data, data->new_line);
		data->i_buffer++;
	}
	else
		data->new_line[data->i_new_line++] = data->buffer[data->i_buffer++];
}

void	clean_buffer4(t_data *data)
{
	data->new_line[data->i_new_line] = data->buffer[data->i_buffer];
	data->i_buffer++;
	data->i_new_line++;
	data->new_line[data->i_new_line++] = data->buffer[data->i_buffer];
}

void	clean_buffer3(t_data *data)
{
	clear_quote(data, data->buffer[data->i_buffer]);
	data->new_line[data->i_new_line] = data->buffer[data->i_buffer];
	data->i_buffer++;
	data->i_new_line++;
	while (data->buffer[data->i_buffer] != '"'
		&& data->buffer[data->i_buffer] != '\0')
	{
		if (data->buffer[data->i_buffer] == '$')
			clean_var(data, data->new_line);
		else
			data->new_line[data->i_new_line++]
				= data->buffer[data->i_buffer++];
	}
	if (data->buffer[data->i_buffer] == '"')
		clear_quote(data, data->buffer[data->i_buffer]);
	data->new_line[data->i_new_line] = data->buffer[data->i_buffer];
	data->i_buffer++;
	data->i_new_line++;
}
