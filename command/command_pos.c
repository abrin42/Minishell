/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 05:14:28 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 05:14:29 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_cmd_start1(t_data *data, int *pipe_in)
{
	data->condition = 0;
	if (check_redirect_inverse(data) == 0 && (command_exist(data) == 0
			|| command_exist(data) == 1))
	{
		if (search_in_file(data, data->token_y) != -1)
			execute_search_pipe_start(data, pipe_in);
		else
			execute_search_pipe_void(data, pipe_in);
	}
	else if (check_redirect_inverse(data) == 2 && (command_exist(data) == 0
			|| command_exist(data) == 1))
		execute_search_in_pipe(data, pipe_in);
	else
		pipe_start(data, pipe_in);
}

void	execute_cmd_middle1(t_data *data, int *pipe_in, int *fd_pipe)
{
	if (check_redirect_pipe(data) == 0)
		execute_in_file_pipe(data, data->token_y, fd_pipe);
	else if (check_redirect_inverse(data) == 0
		&& (command_exist(data) == 0 || command_exist(data) == 1))
	{
		if (search_in_file(data, data->token_y) != -1)
			execute_search_pipe_middle(data, fd_pipe, pipe_in);
		else
			execute_search_pipe_void(data, pipe_in);
	}
	else if (check_redirect_inverse(data) == 2 && (command_exist(data) == 0
			|| command_exist(data) == 1))
		execute_search_in_pipe(data, pipe_in);
	else
		pipe_middle(data, fd_pipe, pipe_in);
}

void	execute_cmd_end1(t_data *data, int *pipe_in, int *fd_pipe)
{
	if (check_redirect_pipe(data) == 0)
		execute_in_file_pipe(data, data->token_y, fd_pipe);
	else if (check_redirect_inverse(data) == 0
		&& (command_exist(data) == 0 || command_exist(data) == 1))
	{
		if (search_in_file(data, data->token_y) != -1)
			execute_search_pipe_end(data, fd_pipe);
		else
			execute_search_pipe_void(data, pipe_in);
	}
	else if (check_redirect_inverse(data) == 2 && (command_exist(data) == 0
			|| command_exist(data) == 1))
		execute_search_in_pipe_end(data, pipe_in);
	else
		pipe_end(data, fd_pipe);
}
