/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 05:42:39 by abrin             #+#    #+#             */
/*   Updated: 2023/08/06 05:42:40 by abrin            ###   ########.fr       */
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

void	execute_redirect(t_data *data, int y)
{
	if (ft_strcmp(data->token[y], "echo") == 0)
		ft_echo(data);
	if (ft_strcmp(data->token[y], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->token[y], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(data->token[y], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->token[y], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->token[y], "unset") == 0)
		ft_unset(data);
	else if (ft_strcmp(data->token[y], "exit") == 0)
		ft_exit(data);
	else
		execute_command_redirect(data, y);
}

int	command_exist_redirect2(t_data *data, int y)
{
	if (ft_strcmp(data->token[y], "echo") == 0)
		return (0);
	else if (ft_strcmp(data->token[y], "cd") == 0)
		return (0);
	else if (ft_strcmp(data->token[y], "pwd") == 0)
		return (0);
	else if (ft_strcmp(data->token[y], "env") == 0)
		return (0);
	else if (ft_strcmp(data->token[y], "export") == 0)
		return (0);
	else if (ft_strcmp(data->token[y], "unset") == 0)
		return (0);
	else if (ft_strcmp(data->token[y], "exit") == 0)
		return (0);
	return (-1);
}

int	command_exist_redirect(t_data *data, int y)
{
	if (command_exist_redirect2(data, y) == 0)
		return (0);
	else
	{
		data->count_path = count_path(getenv("PATH"));
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

void	redirection_in_file(t_data *data, int y)
{
	char	mes[500];
	int		rd_bytes;
	pid_t	pid;
	int		status_pid;
	int		fd;

	if (ft_strcmp(data->token[y], ">") == 0)
		fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(data->token[y], ">>") == 0)
		fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	rd_bytes = read(data->tube_redirect[0], mes, 499);
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
		execve(data->path, data->args, data->env);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	execute_in_file_first_pipe(t_data *data, int y, int *fd_pipe)
{
	pid_t	pid;
	int		fd;
	char	*str;
	int		buf_str;

	while (data->token[y][0] != '>')
		y++;
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

void	execute_in_file_pipe3(t_data *data, int y, int *fd_pipe, int fd)
{
	close(fd_pipe[1]);
	dup2(fd_pipe[0], 0);
	dup2(fd, 1);
	execute_redirect(data, y);
	close(fd);
}

void	execute_in_file_pipe_open(t_data *data)
{
	if (ft_strcmp(data->token[data->x], ">") == 0)
		data->fd = open(data->token[data->x + 1], 01 | 0100 | O_TRUNC, 0644);
	else if (ft_strcmp(data->token[data->x], ">>") == 0)
		data->fd = open(data->token[data->x + 1], 01 | 0100 | O_APPEND, 0644);
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
	while (data->token[data->x][0] != '>')
		data->x++;
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

void	search_in_file_error(t_data *data)
{
	perror(data->token[data->token_y + 2]);
	data->error = 1;
}

void	init_search_in_file(t_data *data)
{
	data->condition2 = 1;
	data->save = gc_malloc(&data->gc, sizeof(char) * 1);
	data->save[0] = '\0';
	data->buf = gc_malloc(&data->gc, sizeof(char) * (50 + 1));
}

void	search_in_file1(t_data *data)
{
	close(data->tube_search[0]);
	while (data->condition2 != 0)
	{
		data->condition2 = read(data->fd1, data->buf, 50);
		data->buf[data->condition2] = '\0';
		data->save = ft_strjoin2(data->save, data->buf, data);
	}
	close(data->fd1);
	dup2(data->tube_search[1], 1);
	printf("%s", data->save);
	close(data->tube_search[1]);
}

int	search_in_file(t_data *data, int y)
{
	pid_t	pid;

	init_search_in_file(data);
	y = y - data->add;
	while (data->token[y][0] != '<')
		y++;
	y++;
	data->fd1 = open(data->token[y], O_RDONLY);
	if (data->fd1 == -1)
	{
		perror(data->token[data->token_y + 2]);
		data->error = 1;
		return (-1);
	}
	pipe(data->tube_search);
	pid = fork();
	if (pid == 0)
	{
		search_in_file1(data);
		exit(0);
	}
	close(data->tube_search[1]);
	waitpid(pid, NULL, 0);
	return (0);
}

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
		dup2(fd_pipe[0], 0);
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

void	execute_in_file(t_data *data, int y)
{
	pid_t	pid;

	if (command_exist_redirect(data, y) == -1)
		return ;
	pipe(data->tube_redirect);
	pid = fork();
	if (pid == 0)
	{
		close(data->tube_redirect[0]);
		dup2(data->tube_redirect[1], 1);
		execute_redirect(data, y);
		exit (0);
	}
	close(data->tube_redirect[1]);
	waitpid(pid, NULL, 0);
	while (data->token[y][0] != '>')
		y++;
	redirection_in_file(data, y);
	close(data->tube_redirect[0]);
}

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

int	check_redirect(t_data *data)
{
	int	y;

	y = data->token_y;
	if (data->token[y][0] == '>')
		return (0);
	while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
		y++;
	if (data->token[y][0] == '>')
		return (0);
	return (1);
}

int	check_redirect_inverse(t_data *data)
{
	int	y;

	y = data->token_y;
	while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
		y++;
	if (data->token[y][0] == '<')
		return (0);
	return (1);
}
