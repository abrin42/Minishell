/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_search_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 06:30:29 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 06:30:30 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_search_pipe_void(t_data *data, int *fd_pipe)
{
	close(fd_pipe[1]);
	while (data->token[data->token_y][0] != '|'
			&& data->token[data->token_y][0] != '\0')
	{
		data->add++;
		data->token_y++;
	}
	data->token_y++;
	data->add++;
	data->count_pipe--;
	if (data->token[data->token_y][0] != '\0')
		execute_cmd(data, fd_pipe[0]);
}

void	execute_search_pipe_middle1(t_data *data, int *fd_in, int *fd_out)
{
	close(fd_in[1]);
	close(fd_out[0]);
	close(data->tube_search[1]);
	dup2(fd_in[0], 0);
	dup2(fd_out[1], 1);
	dup2(data->tube_search[0], 0);
	execute(data);
	close(data->tube_search[0]);
	close(fd_in[0]);
	close(fd_out[1]);
}

void	execute_search_pipe_middle(t_data *data, int *fd_in, int *fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_search_pipe_middle1(data, fd_in, fd_out);
		exit (0);
	}
	close(fd_in[0]);
	close(fd_out[1]);
	close(data->tube_search[1]);
	waitpid(pid, NULL, 0);
	close(data->tube_search[0]);
	while (data->token[data->token_y][0] != '|'
		&& data->token[data->token_y][0] != '\0')
	{
		data->add++;
		data->token_y++;
	}
	data->token_y++;
	data->add++;
	data->count_pipe--;
	if (data->token[data->token_y][0] != '\0')
		execute_cmd(data, fd_out[0]);
}

void	execute_search_pipe_end(t_data *data, int *fd_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd_pipe[1]);
		close(data->tube_search[1]);
		dup2(data->tube_search[0], 0);
		execute(data);
		close(data->tube_search[0]);
		close(fd_pipe[0]);
		exit (0);
	}
	close(fd_pipe[0]);
	close(data->tube_search[1]);
	waitpid(pid, NULL, 0);
	close(data->tube_search[0]);
	close(fd_pipe[1]);
}
