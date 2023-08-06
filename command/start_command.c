/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 04:57:23 by abrin             #+#    #+#             */
/*   Updated: 2023/08/06 04:57:24 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_exist(t_data *data)
{
	if (ft_strcmp(data->token[data->token_y], "echo") == 0)
		return (0);
	else if (ft_strcmp(data->token[data->token_y], "cd") == 0)
		return (0);
	else if (ft_strcmp(data->token[data->token_y], "pwd") == 0)
		return (0);
	else if (ft_strcmp(data->token[data->token_y], "env") == 0)
		return (0);
	else if (ft_strcmp(data->token[data->token_y], "export") == 0)
		return (0);
	else if (ft_strcmp(data->token[data->token_y], "unset") == 0)
		return (0);
	else if (ft_strcmp(data->token[data->token_y], "exit") == 0)
		return (0);
	else if (data->token[data->token_y][0] == '.' &&
		data->token[data->token_y][1] == '/')
	{
		data->path = "./minishell";
		return (0);
	}
	else
	{
		data->count_path = count_path(getenv("PATH"));
		while (data->count_path > 0)
		{
			data->path = ft_strjoin(data->path_bdd[data->count_path - 1],
					data->token[data->token_y], data);
			if (access(data->path, X_OK) == 0)
				return (1);
			data->count_path--;
		}
	}
	return (-1);
}

void	execute_bultins(t_data *data)
{
	if (ft_strcmp(data->token[data->token_y], "echo") == 0)
		ft_echo(data);
	if (ft_strcmp(data->token[data->token_y], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->token[data->token_y], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(data->token[data->token_y], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->token[data->token_y], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->token[data->token_y], "unset") == 0)
		ft_unset(data);
	else if (ft_strcmp(data->token[data->token_y], "exit") == 0)
		ft_exit(data);
}

void	execute_command(t_data *data)
{
	int		i;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		malloc_args(data);
		init_args(data);
		execve(data->path, data->args, data->env);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}

void	execute(t_data *data)
{
	if (ft_strcmp(data->token[data->token_y], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->token[data->token_y], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(data->token[data->token_y], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(data->token[data->token_y], "env") == 0)
		ft_env(data);
	else if (ft_strcmp(data->token[data->token_y], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(data->token[data->token_y], "unset") == 0)
		ft_unset(data);
	else if (ft_strcmp(data->token[data->token_y], "exit") == 0)
		ft_exit(data);
	else
		execute_command(data);
}

void	execute_cmd(t_data *data, int fd_pipe)
{
	int	pipe_[2];

	pipe(pipe_);
	if (data->condition == 1)
	{
		if (check_redirect_inverse(data) == 0 && (command_exist(data) == 0
				|| command_exist(data) == 1))
		{
			data->condition = 0;
			if (search_in_file(data, data->token_y) != -1)
				execute_search_pipe_start(data, pipe_);
			else
				execute_search_pipe_void(data, pipe_);
		}
		else
		{
			data->condition = 0;
			pipe_start(data, pipe_);
		}
	}
	else if (data->condition == 0 && data->count_pipe > 0)
	{
		if (check_redirect_pipe(data) == 0)
			execute_in_file_pipe(data, data->token_y, &fd_pipe);
		else if (check_redirect_inverse(data) == 0
			&& (command_exist(data) == 0 || command_exist(data) == 1))
		{
			if (search_in_file(data, data->token_y) != -1)
				execute_search_pipe_middle(data, &fd_pipe, pipe_);
			else
				execute_search_pipe_void(data, pipe_);
		}
		else
			pipe_middle(data, &fd_pipe, pipe_);
	}
	else
	{
		if (check_redirect_pipe(data) == 0)
			execute_in_file_pipe(data, data->token_y, &fd_pipe);
		else if (check_redirect_inverse(data) == 0
			&& (command_exist(data) == 0 || command_exist(data) == 1))
		{
			if (search_in_file(data, data->token_y) != -1)
				execute_search_pipe_end(data, &fd_pipe);
			else
				execute_search_pipe_void(data, pipe_);
		}
		else
			pipe_end(data, &fd_pipe);
	}
}

void	start_command(t_data *data)
{
	data->token_x = 0;
	data->token_y = 0;
	data->condition = 1;
	malloc_path_bdd(data);
	if (data->count_pipe > 0)
		execute_cmd(data, 0);
	else
	{
		if (check_redirect(data) == 0 && (command_exist(data) == 0
				|| command_exist(data) == 1))
			execute_in_file(data, data->token_y);
		else if (check_redirect_inverse(data) == 0
			&& (command_exist(data) == 0 || command_exist(data) == 1))
		{
			if (search_in_file(data, 0) == 0)
				execute_search(data);
		}
		else if (command_exist(data) == 0 || command_exist(data) == 1)
			execute(data);
		else
		{
			data->error = 127;
			printf("%s: command not found\n", data->token[data->token_y]);
		}
	}
}
