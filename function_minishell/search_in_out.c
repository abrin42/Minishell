/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:36:03 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 03:56:54 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	promt_in_out(t_data *data, int *pipe_sio, ssize_t bytes_read)
{
	while (42)
	{
		bytes_read = promt_in_out_init(data, bytes_read);
		if (ft_strlen(data->buffer_sio) > 0)
		{
			signal(SIGINT, handle_signal);
			signal(SIGQUIT, SIG_IGN);
			if (data->token[data->token_y + 1][0] == '<'
				&& data->token[data->token_y + 1][1] == '<')
			{
				if (ft_strcmp3(data->buffer_sio, data->token
						[data->token_y + 2]) == 0)
					break ;
			}
			else if (data->token[data->token_y + 2][0] == '<'
				&& data->token[data->token_y + 2][1] == '<')
			{
				if (ft_strcmp3(data->buffer_sio, data->token
						[data->token_y + 3]) == 0)
					break ;
			}
			write(pipe_sio[1], data->buffer_sio, bytes_read);
		}
	}
}

void	dup2_search_in_out(t_data *data, int *pipe_sio)
{
	close(pipe_sio[1]);
	dup2(pipe_sio[0], 0);
	malloc_args(data);
	init_args(data);
	execute(data);
	close(pipe_sio[0]);
	exit(0);
}

void	search_in_out2(t_data *data, pid_t	pid2, int	*pipe_sio)
{
	pid2 = fork();
	if (pid2 == 0)
		dup2_search_in_out(data, pipe_sio);
	close(pipe_sio[1]);
	close(pipe_sio[0]);
	waitpid(pid2, NULL, 0);
	check_error(data);
}

void	execute_command_search_in_out(t_data *data)
{
	int		pipe_sio[2];
	pid_t	pid;
	pid_t	pid2;
	ssize_t	bytes_read;

	if (check_in_out(data) == -1)
		return ;
	g_condition_error = 42;
	pipe(pipe_sio);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_sio[0]);
		promt_in_out(data, pipe_sio, bytes_read);
		close(pipe_sio[1]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	if (g_condition_error == 1)
		return ;
	search_in_out2(data, pid2, pipe_sio);
}
