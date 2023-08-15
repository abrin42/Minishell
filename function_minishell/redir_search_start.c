/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_search_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 06:46:28 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 03:36:57 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_search(t_data *data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		close(data->tube_search[1]);
		dup2(data->tube_search[0], 0);
		execute(data);
		close(data->tube_search[0]);
		exit (0);
	}
	close(data->tube_search[1]);
	waitpid(pid, NULL, 0);
	close(data->tube_search[0]);
}

void	execute_search_pipe_start3(t_data *data, int *fd_pipe)
{
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

void	execute_search_pipe_start2(t_data *data, int *fd_pipe)
{
	close(fd_pipe[0]);
	close(data->tube_search[1]);
	dup2(data->tube_search[0], 0);
	dup2(fd_pipe[1], 1);
	execute(data);
	close(data->tube_search[0]);
	close(fd_pipe[1]);
}

void	execute_search_pipe_start(t_data *data, int *fd_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execute_search_pipe_start2(data, fd_pipe);
		exit (0);
	}
	close(fd_pipe[1]);
	close(data->tube_search[1]);
	waitpid(pid, NULL, 0);
	close(data->tube_search[0]);
	execute_search_pipe_start3(data, fd_pipe);
}
