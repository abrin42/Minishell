/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 05:53:53 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 02:13:21 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	advance_fill_token_operator(t_data *data)
{
	data->token[data->token_y][data->token_x] = data->buffer[data->i];
	data->token_x++;
	data->i++;
}

void	fill_token3(t_data *data)
{
	advance_fill_token_operator(data);
	if (!ft_is_operator(data->buffer[data->i]) && !ft_iswhitespace
		(data->buffer[data->i]) && data->buffer[data->i] != '\0')
		fill_token_quote_new_line(data);
}

void	fill_token2(t_data *data)
{
	if (data->buffer[data->i] == '\'' || data->buffer[data->i] == '"')
	{
		data->i = fill_token_quote(data, data->i);
	}
	while (!ft_is_operator(data->buffer[data->i])
		&& !ft_iswhitespace(data->buffer[data->i])
		&& data->buffer[data->i] != '\0')
	{
		if (data->buffer[data->i] == '\'' || data->buffer[data->i] == '"')
			data->i = fill_token_quote(data, data->i);
		else
		{
			data->token[data->token_y][data->token_x] = data->buffer[data->i];
			data->token_x++;
			data->i++;
		}
	}
	data->token[data->token_y][data->token_x] = '\0';
	while (ft_iswhitespace(data->buffer[data->i])
		&& data->buffer[data->i] != '\0')
		data->i++;
}

void	init_data_token(t_data *data)
{
	data->i = 0;
	data->token_x = 0;
	data->count_pipe2 = 0;
	data->count_redirect = 0;
}

void	fill_token(t_data *data)
{
	init_data_token(data);
	if (data->pipe_not_close == 0)
		clean_token(data);
	else
		data->token_y++;
	while (data->buffer[data->i] != '\0')
	{
		fill_token2(data);
		if (data->buffer[data->i] == '\0')
			return ;
		fill_token_quote_new_line(data);
		if (data->buffer[data->i] == '\'' || data->buffer[data->i] == '"')
			data->i = fill_token_quote(data, data->i);
		init_count_pipe_redirect(data);
		while (ft_is_operator(data->buffer[data->i])
			&& data->buffer[data->i] != '\0')
		{
			count_pipe_redirect(data);
			if (data->count_pipe2 > 1 || data->count_redirect > 2)
				return ;
			fill_token3(data);
		}
	}
}
