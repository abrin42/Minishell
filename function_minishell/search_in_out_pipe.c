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

/*void		execute_search_in_pipe_middle(t_data *data, int *fd_pipe_in, int *fd_pipe_out)
{
	int	pipe_sio[2];
	pid_t	pid;
	pid_t	pid2;
	ssize_t bytes_read;

	pipe(pipe_sio);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_sio[0]);
		while (42)
		{
			clear_buffer_sio(data);
			bytes_read = read(STDIN_FILENO, data->buffer_sio, sizeof(data->buffer_sio));
			if (ft_strlen(data->buffer_sio) > 0)
			{
				if (data->token[data->token_y + 1][0] == '<' && data->token[data->token_y + 1][1] == '<')
				{
					if (ft_strcmp3(data->buffer_sio, data->token[data->token_y + 2]) == 0)
						break;
				}
				else if (data->token[data->token_y + 2][0] == '<' && data->token[data->token_y + 2][1] == '<')
				{
					if (ft_strcmp3(data->buffer_sio, data->token[data->token_y + 3]) == 0)
						break;
				}
				write(pipe_sio[1], data->buffer_sio, bytes_read);
			}
		}
		close(pipe_sio[1]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipe_sio[1]);
		close(fd_pipe_in[1]);
		close(fd_pipe_out[0]);
		dup2(pipe_sio[0], 0);
		dup2(fd_pipe_in[0], 0);
		dup2(fd_pipe_out[1], 1);
		malloc_args(data);
		init_args(data);
		execve(data->path, data->args, data->env);
		close(pipe_sio[0]);
		close(fd_pipe_out[1]);
		exit(0);
	}
	close(pipe_sio[1]);
	close(pipe_sio[0]);
	close(fd_pipe_in[0]);
	close(fd_pipe_out[1]);
	waitpid(pid2, NULL, 0);
	pipe_avance(data);
	execute_cmd(data, fd_pipe_out[0]);
}*/

void		execute_search_in_pipe(t_data *data, int *fd_pipe)
{
	int	pipe_sio[2];
	pid_t	pid;
	pid_t	pid2;
	ssize_t bytes_read;

	pipe(pipe_sio);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_sio[0]);
		while (42)
		{
			clear_buffer_sio(data);
			bytes_read = read(STDIN_FILENO, data->buffer_sio, sizeof(data->buffer_sio));
			if (ft_strlen(data->buffer_sio) > 0)
			{
				if (data->token[data->token_y + 1][0] == '<' && data->token[data->token_y + 1][1] == '<')
				{
					if (ft_strcmp3(data->buffer_sio, data->token[data->token_y + 2]) == 0)
						break;
				}
				else if (data->token[data->token_y + 2][0] == '<' && data->token[data->token_y + 2][1] == '<')
				{
					if (ft_strcmp3(data->buffer_sio, data->token[data->token_y + 3]) == 0)
						break;
				}
				write(pipe_sio[1], data->buffer_sio, bytes_read);
			}
		}
		close(pipe_sio[1]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipe_sio[1]);
		close(fd_pipe[0]);
		dup2(pipe_sio[0], 0);
		dup2(fd_pipe[1], 1);
		malloc_args(data);
		init_args(data);
		execve(data->path, data->args, data->env);
		close(pipe_sio[0]);
		close(fd_pipe[1]);
		exit(0);
	}
	close(pipe_sio[1]);
	close(pipe_sio[0]);
	close(fd_pipe[1]);
	waitpid(pid2, NULL, 0);
	pipe_avance(data);
	execute_cmd(data, fd_pipe[0]);
	if (command_exist(data) == 0 || command_exist(data) == 1)
		data->error = 0;
	else
		data->error = -1; // a check valeur en cas derreur
}

void		execute_search_in_pipe_end(t_data *data, int *fd_pipe)
{
	int	pipe_sio[2];
	pid_t	pid;
	pid_t	pid2;
	ssize_t bytes_read;

	pipe(pipe_sio);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_sio[0]);
		while (42)
		{
			clear_buffer_sio(data);
			bytes_read = read(STDIN_FILENO, data->buffer_sio, sizeof(data->buffer_sio));
			if (ft_strlen(data->buffer_sio) > 0)
			{
				if (data->token[data->token_y + 1][0] == '<' && data->token[data->token_y + 1][1] == '<')
				{
					if (ft_strcmp3(data->buffer_sio, data->token[data->token_y + 2]) == 0)
						break;
				}
				else if (data->token[data->token_y + 2][0] == '<' && data->token[data->token_y + 2][1] == '<')
				{
					if (ft_strcmp3(data->buffer_sio, data->token[data->token_y + 3]) == 0)
						break;
				}
				write(pipe_sio[1], data->buffer_sio, bytes_read);
			}
		}
		close(pipe_sio[1]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipe_sio[1]);
		close(fd_pipe[0]);
		dup2(pipe_sio[0], 0);
		//dup2(fd_pipe[1], 1);
		malloc_args(data);
		init_args(data);
		execve(data->path, data->args, data->env);
		close(pipe_sio[0]);
		close(fd_pipe[1]);
		exit(0);
	}
	close(pipe_sio[1]);
	close(pipe_sio[0]);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	waitpid(pid2, NULL, 0);
}
