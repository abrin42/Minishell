/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 05:41:14 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 02:21:51 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_buffer2(t_data *data)
{
	clear_quote(data, data->buffer[data->i_buffer]);
	data->new_line[data->i_new_line] = data->buffer[data->i_buffer];
	data->i_buffer++;
	data->i_new_line++;
	while (data->buffer[data->i_buffer] != '\''
		&& data->buffer[data->i_buffer] != '\0')
	{
		data->new_line[data->i_new_line++] = data->buffer[data->i_buffer++];
	}
	if (data->buffer[data->i_buffer] == '\'')
		clear_quote(data, data->buffer[data->i_buffer]);
	data->new_line[data->i_new_line] = data->buffer[data->i_buffer];
	data->i_new_line++;
	data->i_buffer++;
}

void	clean_buffer1(t_data *data)
{
	while (data->buffer[data->p] != ' '
		&& data->buffer[data->p] != '\0')
		data->p++;
	while (data->buffer[data->p] != '/')
		data->p--;
	while (data->i_buffer++ != data->p)
		data->i_buffer++;
}

void	init_clean_buffer(t_data *data)
{
	data->new_line = gc_malloc(&data->gc, sizeof(char) * 10000);
	data->i_new_line = 0;
	data->i_buffer = 0;
	data->simple_quote = 0;
	data->double_quote = 0;
}

void	clean_path_buffer(t_data *data)
{
	while (data->buffer[data->i_buffer] != ' '
		&& data->buffer[data->i_buffer] != '\0')
	{
		data->new_line[data->i_new_line] = data->buffer[data->i_buffer];
		data->i_new_line++;
		data->i_buffer++;
	}
}

char	*clean_buffer(t_data *data)
{
	init_clean_buffer(data);
	while (data->i_buffer < ft_strlen(data->buffer))
	{
		if (data->buffer[data->i_buffer] == 'P'
			&& data->buffer[data->i_buffer + 1] == 'A'
			&& data->buffer[data->i_buffer + 2] == 'T'
			&& data->buffer[data->i_buffer + 3] == 'H'
			&& data->buffer[data->i_buffer + 4] == '=')
		{
			clean_path_buffer(data);
		}
		clean_buffer5(data);
	}
	data->new_line[data->i_new_line] = '\0';
	return (data->new_line);
}
