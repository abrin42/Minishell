/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_out_pipe2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 09:29:04 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 03:14:44 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	srch_pipe2(t_data *data, pid_t pid2, int *pipe_sio, int *fd_pipe)
{
	pid2 = fork();
	if (pid2 == 0)
		dup2_search_in_pipe(data, pipe_sio, fd_pipe);
	search_in_pipe_close(data, pipe_sio, fd_pipe);
	waitpid(pid2, NULL, 0);
	pipe_avance(data);
	execute_cmd(data, fd_pipe[0]);
	error_search_in_pipe(data);
}

void	srch_end2(t_data *data, pid_t pid2, int *pipe_sio, int *fd_pipe)
{
	pid2 = fork();
	if (pid2 == 0)
		dup2_search_in_pipe_end(data, pipe_sio, fd_pipe);
	search_in_pipe_close(data, pipe_sio, fd_pipe);
	close(fd_pipe[0]);
	waitpid(pid2, NULL, 0);
	error_search_in_pipe(data);
}

void	search_in_pipe_close(t_data *data, int *pipe_sio, int *fd_pipe)
{
	close(pipe_sio[1]);
	close(pipe_sio[0]);
	close(fd_pipe[1]);
}

void	dup2_search_in_pipe_end(t_data *data, int *pipe_sio, int *fd_pipe)
{
	close(pipe_sio[1]);
	close(fd_pipe[0]);
	dup2(pipe_sio[0], 0);
	malloc_args(data);
	init_args(data);
	execute(data);
	close(pipe_sio[0]);
	close(fd_pipe[1]);
	exit(0);
}

void	check_error(t_data *data)
{
	if (command_exist(data) == 0 || command_exist(data) == 1)
		data->error = 0;
	else
		data->error = 130;
}
