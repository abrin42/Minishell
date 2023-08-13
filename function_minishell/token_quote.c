/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 06:04:34 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 06:04:35 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_token_quote_condition(t_data *data, int i)
{
	data->condition1 = 0;
	if (data->buffer[i] == '\'')
		data->condition1 = 1;
	else if (data->buffer[i] == '"')
		data->condition1 = 2;
}

void	fill_token_quote_new_line(t_data *data)
{
	data->token_y++;
	data->token_x = 0;
}

void	clear_quote(t_data *data, char c)
{
	if (c == '\'' && data->simple_quote == 0)
		data->simple_quote++;
	else if (c == '\"' && data->double_quote == 0)
		data->double_quote++;
	else if (c == '\'' && data->simple_quote == 1)
		data->simple_quote--;
	else if (c == '\"' && data->double_quote == 1)
		data->double_quote--;
}

char	*ft_parsing_space_quote(t_data *data)
{
	int		i;
	int		j;
	char	*line;

	line = gc_malloc(&data->gc, sizeof(char) * (ft_strlen
				(data->token[data->token_y]) + 1));
	i = 0;
	j = 0;
	while (data->token[data->token_y][i] == ' '
		&& data->token[data->token_y][i] != '\0')
		i++;
	while (data->token[data->token_y][i]
		&& data->token[data->token_y][i] != '\0')
	{
		if ((data->token[data->token_y][i] == ' ' && data->token
			[data->token_y][i + 1] == ' '))
			i++;
		else
			line[j++] = data->token[data->token_y][i++];
	}
	line[j] = '\0';
	return (line);
}

int	fill_token_quote(t_data *data, int i)
{
	fill_token_quote_condition(data, i);
	i++;
	if (data->condition1 == 1)
		i = fill_token_quote_condition1(data, i);
	else if (data->condition1 == 2)
	{
		while (data->buffer[i] != '\"')
		{
			if (token_quote_empty(data, i) == 1)
				i++;
			else
			{
				data->token[data->token_y][data->token_x] = data->buffer[i];
				i++;
				data->token_x++;
			}
		}
		data->token[data->token_y][data->token_x] = '\0';
		i++;
	}
	return (i);
}
