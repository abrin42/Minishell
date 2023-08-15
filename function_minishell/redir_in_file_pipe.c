/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_file_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 07:13:32 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 03:53:45 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_in_file_pipe(t_data *data, int y)
{
	int	start;
	int	end_y;

	start = y;
	while (data->token[y][0] != '|' && data->token[y][0] != '\0')
		y++;
	while (data->token[y][0] != '>')
		y--;
	end_y = y;
	while (y != start)
	{
		if (ft_strcmp(data->token[y], ">") != 0
			&& (ft_strcmp(data->token[y], ">>") != 0))
			open(data->token[y], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		y--;
	}
	return (end_y);
}

void	execute_in_file_first_pipe(t_data *data, int y, int *fd_pipe)
{
	pid_t	pid;
	int		fd;
	char	*str;
	int		buf_str;

	y = open_in_file_pipe(data, y);
	if (ft_strcmp(data->token[y], ">") == 0)
		fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(data->token[y], ">>") == 0)
		fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	str = malloc(sizeof(char) * 10000);
	buf_str = read(fd_pipe[0], str, 9999);
	str[buf_str] = '\0';
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);
		printf("%s", str);
		close (fd);
		exit (0);
	}
	close (fd);
}

void	execute_in_file_pipe2(t_data *data, int *fd_pipe)
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

void	execute_in_file_pipe(t_data *data, int y, int *fd_pipe)
{
	pid_t	pid;
	char	*str;

	str = malloc(sizeof(char) * 1000);
	if (command_exist_redirect(data, y) == -1)
		return ;
	pid = fork();
	data->x = y;
	data->x = open_in_file_pipe(data, data->x);
	execute_in_file_pipe_open(data);
	if (pid == 0)
	{
		execute_in_file_pipe3(data, y, fd_pipe, data->fd);
		data->buf_str = read(fd_pipe[0], str, 999);
		str[data->buf_str] = '\0';
		close(fd_pipe[0]);
		exit (0);
	}
	waitpid(pid, NULL, 0);
	close(data->fd);
	close(fd_pipe[1]);
	execute_in_file_pipe2(data, fd_pipe);
}
