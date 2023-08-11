/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_out_pipe2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 09:29:04 by abrin             #+#    #+#             */
/*   Updated: 2023/08/11 09:29:04 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
