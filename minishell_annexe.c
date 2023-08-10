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

void	handle_signal(int i)
{
	(void) i;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
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

void	prompt3(t_data *data)
{
	init_data(data);
	add_history(data->buffer);
	data->buffer = clean_buffer(data);
	if (data->simple_quote == 0 && data->double_quote == 0)
		fill_token(data);
}

void	prompt2(t_data *data)
{
	if (ft_strlen(data->buffer) > 0)
	{
		if (data->pipe_not_close == 0)
			prompt3(data);
		else
		{
			add_history(data->buffer);
			data->buffer = clean_buffer(data);
			fill_token(data);
			data->pipe_not_close--;
		}
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
			for (size_t i = 0; i < 6; i++)
			{
				printf("token *%s*\n", data->token[i]);
			}

			start_command(data);
		}
	}
}