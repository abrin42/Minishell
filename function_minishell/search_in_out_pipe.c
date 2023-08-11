/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_out_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 08:30:20 by abrin             #+#    #+#             */
/*   Updated: 2023/08/08 08:30:21 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	search_in_avance(t_data *data)
{
	data->add = 0;
	while (data->token[data->token_y][0] != '|')
	{
		data->add++;
		data->token_y++;
	}
	data->count_pipe--;
	data->token_y++;
	data->add++;
}

void	dup2_search_in_pipe(t_data	*data, int *pipe_sio, int *fd_pipe)
{
	close(pipe_sio[1]);
	close(fd_pipe[0]);
	dup2(pipe_sio[0], 0);
	dup2(fd_pipe[1], 1);
	malloc_args(data);
	init_args(data);
	execute(data);
	close(pipe_sio[0]);
	close(fd_pipe[1]);
	exit(0);
}

void	error_search_in_pipe(t_data *data)
{
	if (command_exist(data) == 0 || command_exist(data) == 1)
		data->error = 0;
	else
		data->error = 130;
}

void	execute_search_in_pipe(t_data *data, int *fd_pipe)
{
	int		pipe_sio[2];
	pid_t	pid;
	pid_t	pid2;
	ssize_t	bytes_read;

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
	pid2 = fork();
	if (pid2 == 0)
		dup2_search_in_pipe(data, pipe_sio, fd_pipe);
	close(pipe_sio[1]);
	close(pipe_sio[0]);
	close(fd_pipe[1]);
	waitpid(pid2, NULL, 0);
	pipe_avance(data);
	execute_cmd(data, fd_pipe[0]);
	error_search_in_pipe(data);
}

void	execute_search_in_pipe_end(t_data *data, int *fd_pipe)
{
	int		pipe_sio[2];
	pid_t	pid;
	pid_t	pid2;
	ssize_t	bytes_read;

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
	pid2 = fork();
	if (pid2 == 0)
		dup2_search_in_pipe_end(data, pipe_sio, fd_pipe);
	close(pipe_sio[1]);
	close(pipe_sio[0]);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	waitpid(pid2, NULL, 0);
	error_search_in_pipe(data);
}
