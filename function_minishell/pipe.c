/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 05:42:33 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 01:23:06 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_start(t_data *data, int *fd_pipe)
{
	pid_t	pid;
	int		y;

	y = -1;
	if (check_redirect_pipe(data) == 0)
		y = data->token_y;
	pid = fork();
	if (pid == 0)
	{
		close(fd_pipe[0]);
		dup2(fd_pipe[1], 1);
		if (command_exist(data) == 0 || command_exist(data) == 1)
			execute(data);
		else
			ft_putstr_error(data, data->token[data->token_y]);
		close(fd_pipe[1]);
		exit(0);
	}
	close(fd_pipe[1]);
	waitpid(pid, NULL, 0);
	pipe_avance(data);
	if (y != -1)
		execute_in_file_first_pipe(data, y, fd_pipe);
	execute_cmd(data, fd_pipe[0]);
}

void	pipe_middle(t_data *data, int *fd_pipe_in, int *fd_pipe_out)
{
	int		status_pid;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd_pipe_in[1]);
		close(fd_pipe_out[0]);
		dup2(fd_pipe_in[0], STDIN_FILENO);
		dup2(fd_pipe_out[1], STDOUT_FILENO);
		if (command_exist(data) == 0 || command_exist(data) == 1)
			execute(data);
		else
			ft_putstr_error(data, data->token[data->token_y]);
		exit(0);
	}
	close(fd_pipe_in[0]);
	close(fd_pipe_out[1]);
	waitpid(pid, &status_pid, 0);
	pipe_avance(data);
	execute_cmd(data, fd_pipe_out[0]);
}

void	pipe_end(t_data *data, int *fd_pipe)
{
	pid_t	pid;
	int		status_pid;

	pid = fork();
	if (pid == 0)
	{
		close(fd_pipe[1]);
		dup2(fd_pipe[0], STDIN_FILENO);
		if (command_exist(data) == 0 || command_exist(data) == 1)
			execute(data);
		close(fd_pipe[0]);
		exit(0);
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid, &status_pid, 0);
	if (command_exist(data) == -1)
		ft_putstr_error(data, data->token[data->token_y]);
	else if (command_exist(data) == 0 || command_exist(data) == 1)
		data->error = 0;
}

void	pipe_avance(t_data *data)
{
	data->add = 0;
	while (data->token[data->token_y][0] != '|')
	{
		data->add++;
		data->token_y++;
	}
	data->token_y++;
	data->add++;
	data->count_pipe--;
}
