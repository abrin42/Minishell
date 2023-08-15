/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_file_pipe2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 03:55:57 by tmarie            #+#    #+#             */
/*   Updated: 2023/08/15 03:55:58 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redirect_pipe(t_data *data)
{
	int	y;

	y = data->token_y;
	while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
		y++;
	if (data->token[y][0] == '>')
		return (0);
	return (1);
}

void	execute_in_file_pipe3(t_data *data, int y, int *fd_pipe, int fd)
{
	close(fd_pipe[1]);
	dup2(fd_pipe[0], 0);
	dup2(fd, 1);
	execute_redirect(data, y);
	close(fd);
}
