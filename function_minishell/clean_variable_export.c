/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_variable_export.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 05:28:56 by abrin             #+#    #+#             */
/*   Updated: 2023/08/06 05:28:58 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	check_bin(t_data *data)
{
	char	*new;
	char	*new1;

	new = ft_strjoin3("/bin/", data->buffer, data, data->p);
	new1 = ft_strjoin3("/bin/", data->buffer, data, data->p);
	if (ft_strcmp(data->buffer, new) != 0)
	{
		free(new);
		free(new1);
		return (1);
	}
	if (ft_strcmp(data->buffer, new) != 0)
	{
		free(new);
		free(new1);
		return (1);
	}
	free(new);
	free(new1);
	return (0);
}

void	init_clean_buffer(t_data *data)
{
	data->new_line = gc_malloc(&data->gc, sizeof(char) * 10000);
	data->i_new_line = 0;
	data->i_buffer = 0;
	data->simple_quote = 0;
	data->double_quote = 0;
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

void	clean_buffer4(t_data *data)
{
	data->new_line[data->i_new_line] = data->buffer[data->i_buffer];
	data->i_buffer++;
	data->i_new_line++;
	data->new_line[data->i_new_line++] = data->buffer[data->i_buffer];
}

void	clean_buffer5(t_data *data)
{
	if (data->buffer[data->i_buffer] == '\'')
		clean_buffer2(data);
	else if (data->buffer[data->i_buffer] == '"')
		clean_buffer3(data);
	else if ((data->buffer[data->i_buffer] == '$'
			&& data->buffer[data->i_buffer + 1] == '?'))
		clean_buffer4(data);
	else if (data->buffer[data->i_buffer] == '$')
		clean_var(data, data->new_line);
	else if (data->buffer[data->i_buffer] == '\\')
		data->new_line[data->i_new_line++] = ' ';
	else
		data->new_line[data->i_new_line++] = data->buffer[data->i_buffer];
}

void	clean_buffer6(t_data *data)
{
	if (data->buffer[data->i_buffer] != '\''
		&& data->buffer[data->i_buffer] != '"')
		data->i_buffer++;
}

char	*clean_buffer(t_data *data)
{
	init_clean_buffer(data);
	while (data->i_buffer < ft_strlen(data->buffer))
	{
		while (data->buffer[data->i_buffer] == '/'
			&& data->buffer[data->i_buffer] != '\0'
			&& ((data->buffer[data->i_buffer] == '/')
				&& (data->buffer[data->i_buffer - 1] != '.')))
		{
			data->p = data->i_buffer;
			if (check_bin(data) == -1)
				break ;
			clean_buffer1(data);
		}
		clean_buffer5(data);
		clean_buffer6(data);
	}
	data->new_line[data->i_new_line] = '\0';
	return (data->new_line);
}

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

char	*ft_parsing_space_quote(t_data *data)
{
	int		i;
	int		j;
	char	*line;

	line = gc_malloc(&data->gc, sizeof(char) * (ft_strlen
				(data->token[data->token_y - 1]) + 1));
	i = 0;
	j = 0;
	while (data->token[data->token_y - 1][i] == ' ')
		i++;
	while (data->token[data->token_y - 1][i])
	{
		if ((data->token[data->token_y - 1][i] == ' ' && data->token
			[data->token_y - 1][i + 1] == ' ') || (data->token[data->token_y
			- 1][i] == ' ' && data->token[data->token_y - 1][i + 1] == '\0'))
			i++;
		else
			line[j++] = data->token[data->token_y - 1][i++];
	}
	line[j] = '\0';
	//gc_free(&data->gc, (void **)&data->token[data->token_y - 1]);
	return (line);
}

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

int	fill_token_quote(t_data *data, int i)
{
	fill_token_quote_condition(data, i);
	i++;
	if (data->condition1 == 1)
	{
		while (data->buffer[i] != '\'')
			data->token[data->token_y][data->token_x++] = data->buffer[i++];
		data->token[data->token_y][data->token_x] = '\0';
		i++;
		fill_token_quote_new_line(data);
	}
	else if (data->condition1 == 2)
	{
		while (data->buffer[i] != '\"')
		{
			data->token[data->token_y][data->token_x] = data->buffer[i];
			i++;
			data->token_x++;
		}
		data->token[data->token_y][data->token_x] = '\0';
		i++;
		fill_token_quote_new_line(data);
	}
	data->token[data->token_y - 1] = ft_parsing_space_quote(data);
	return (i);
}

void	fill_token2(t_data *data)
{
	if (data->buffer[data->i] == '\'' || data->buffer[data->i] == '"')
		data->i = fill_token_quote(data, data->i);
	while (!ft_is_operator(data->buffer[data->i])
		&& !ft_iswhitespace(data->buffer[data->i])
		&& data->buffer[data->i] != '\0')
	{
		data->token[data->token_y][data->token_x] = data->buffer[data->i];
		data->token_x++;
		data->i++;
	}
	data->token[data->token_y][data->token_x] = '\0';
	while (ft_iswhitespace(data->buffer[data->i])
		&& data->buffer[data->i] != '\0')
		data->i++;
}

void	count_pipe_redirect(t_data *data)
{
	if (data->buffer[data->i] == '>')
		data->count_redirect++;
	else if (data->buffer[data->i] == '<')
		data->count_redirect++;
	else if (data->buffer[data->i] == '|')
		data->count_pipe2++;
}

void	init_data_token(t_data *data)
{
	data->i = 0;
	data->token_x = 0;
	data->count_pipe2 = 0;
	data->count_redirect = 0;
}

void	advance_fill_token_operator(t_data *data)
{
			data->token[data->token_y][data->token_x] = data->buffer[data->i];
			data->token_x++;
			data->i++;
}

void	init_count_pipe_redirect(t_data *data)
{
	data->count_pipe2 = 0;
	data->count_redirect = 0;
}

void	fill_token3(t_data *data)
{
	advance_fill_token_operator(data);
	if (!ft_is_operator(data->buffer[data->i]) && !ft_iswhitespace
		(data->buffer[data->i]) && data->buffer[data->i] != '\0')
		fill_token_quote_new_line(data);
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

void	count_pipe(t_data *data)
{
	int	i;

	i = 0;
	data->count_pipe = 0;
	while (data->token[i])
	{
		if (data->token[i][0] == '|')
			data->count_pipe++;
		i++;
	}
}
