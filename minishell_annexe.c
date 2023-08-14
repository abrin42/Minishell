/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_annexe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 08:55:25 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 08:55:26 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->count_path = 0;
	data->count_pipe = 0;
	data->simple_quote = 0;
	data->double_quote = 0;
	data->i_buffer = 0;
	data->i_new_line = 0;
	data->i_var = 0;
	data->condition = 1;
	data->add = 0;
	data->token_y = 0;
	data->token_x = 0;
	data->p = 0;
	data->new_line = NULL;
	data->var = NULL;
	data->save = NULL;
	data->fd = 0;
	data->fd1 = 0;
	data->x = 0;
	data->buf_str = 0;
	data->count_pipe2 = 0;
	data->count_redirect = 0;
}

void	handle_signal(int sig)
{
	if (condition_error == 42)
		condition_error = 1;
	if (condition_error == 43)
		exit(0);
	else
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	test_pipe_end(t_data *data)
{
	int	i;

	i = 0;
	while (data->token[i][0] != '\0')
		i++;
	if (data->token[i - 1][0] == '|')
		return (1);
	return (0);
}

int	prompt3(t_data *data)
{
	init_data(data);
	add_history(data->buffer);
	data->buffer = clean_buffer(data);
	if (data->buffer[0] == ' ' || data->buffer[0] == '\0'
		|| ft_strcmp(data->buffer, "\"\"") == 0
		|| ft_strcmp(data->buffer, "\'\'") == 0)
		return (1);
	if (data->simple_quote == 0 && data->double_quote == 0)
		fill_token(data);
	if (data->token[0][0] == '\0' && data->token[1][0] == '|')
		data->count_pipe2 = 2;
	else if (data->token[0][0] == '\0' && (data->token[1][0] == '<'
		|| data->token[1][0] == '>'))
		data->count_redirect = 3;
	return (0);
}

void	prompt2(t_data *data)
{
	if (ft_strlen(data->buffer) > 0)
	{
		if (data->pipe_not_close == 0)
		{
			if (prompt3(data) == 1)
				return ;
		}
		else
			other_prompt2(data);
		if (data->simple_quote != 0 || data->double_quote != 0)
			printf("A closing quotation mark is missing\n");
		else if (data->count_pipe2 > 1)
			printf("Syntax error near unexpected token '|'\n");
		else if (data->count_redirect > 2)
			printf("Syntax error near unexpected token '>' or '<'\n");
		else if (test_pipe_end(data) == 1)
			data->pipe_not_close++;
		else
		{
			count_pipe(data);
			start_command(data);
		}
	}
}
