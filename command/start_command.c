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
	int	pipe_in[2];

	pipe(pipe_in);
	if (data->condition == 1)
		execute_cmd_start1(data, pipe_in);
	else if (data->count_pipe > 0 && data->condition == 0)
		execute_cmd_middle1(data, pipe_in, &fd_pipe);
	else
		execute_cmd_end1(data, pipe_in, &fd_pipe);
}

void	start_command(t_data *data)
{
	data->token_x = 0;
	data->token_y = 0;
	data->condition = 1;
	if (malloc_path_bdd(data) == 1)
	{
		error_127(data);
		return ;
	}
	if (data->count_pipe > 0)
		execute_cmd(data, 0);
	else
		cmd_solo(data);
}
