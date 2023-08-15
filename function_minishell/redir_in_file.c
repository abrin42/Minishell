/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 07:07:56 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 03:52:35 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_args_redirect(t_data *data, int x)
{
	int	y;
	int	i_args;

	i_args = 1;
	y = x + 1;
	data->args[0] = data->path;
	while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
	{
		data->args[i_args] = data->token[y];
		i_args++;
		y++;
	}
}

int	command_exist_redirect(t_data *data, int y)
{
	if (command_exist_redirect2(data, y) == 0)
		return (0);
	else
	{
		malloc_path_bdd(data);
		ft_getenv_path(data);
		data->count_path = count_path(data->path_temp);
		while (data->count_path > 0)
		{
			data->path = ft_strjoin(data->path_bdd[data->count_path - 1],
					data->token[y], data);
			if (access (data->path, X_OK) == 0)
				return (1);
			data->count_path--;
		}
	}
	return (-1);
}

void	execute_in_file_pipe_open(t_data *data)
{
	if (ft_strcmp(data->token[data->x], ">") == 0)
		data->fd = open(data->token[data->x + 1], 01 | 0100 | O_TRUNC, 0644);
	else if (ft_strcmp(data->token[data->x], ">>") == 0)
		data->fd = open(data->token[data->x + 1], 01 | 0100 | O_APPEND, 0644);
}

void	redirection_in_file(t_data *data, int y)
{
	char	mes[50000];
	int		rd_bytes;
	pid_t	pid;
	int		status_pid;
	int		fd;

	if (ft_strcmp(data->token[y], ">") == 0)
		fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(data->token[y], ">>") == 0)
		fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	rd_bytes = read(data->tube_redirect[0], mes, 49999);
	mes[rd_bytes] = '\0';
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 1);
		printf("%s", mes);
		close(fd);
		exit (0);
	}
	waitpid(pid, &status_pid, 0);
	close(fd);
}

void	execute_command_redirect(t_data *data, int y)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		malloc_args(data);
		init_args_redirect(data, y);
		execve(data->path, data->args, data->export_var);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}
