/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 00:36:03 by abrin             #+#    #+#             */
/*   Updated: 2023/08/08 00:36:04 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_buffer_sio(t_data *data)
{
	int	i;

	i = 0;
	while (data->buffer_sio[i] != '\0')
	{
		data->buffer_sio[i] = '\0';
		i++;
	}

}

void	execute_command_search_in_out(t_data *data)
{
	int	pipe_sio[2];
	pid_t	pid;
	pid_t	pid2;
	ssize_t bytes_read;

	pipe(pipe_sio);
	pid = fork();
	if (pid == 0)
	{
		close(pipe_sio[0]);
		while (42)
		{
			clear_buffer_sio(data);
			bytes_read = read(STDIN_FILENO, data->buffer_sio, sizeof(data->buffer_sio));
			if (ft_strlen(data->buffer_sio) > 0)
			{
				if (data->token[data->token_y + 1][0] == '<' && data->token[data->token_y + 1][1] == '<')
				{
					if (ft_strcmp3(data->buffer_sio, data->token[data->token_y + 2]) == 0)
						break;
				}
				else if (data->token[data->token_y + 2][0] == '<' && data->token[data->token_y + 2][1] == '<')
				{
					if (ft_strcmp3(data->buffer_sio, data->token[data->token_y + 3]) == 0)
						break;
				}
				write(pipe_sio[1], data->buffer_sio, bytes_read);
			}
		}
		close(pipe_sio[1]);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipe_sio[1]);
		dup2(pipe_sio[0], 0);
		malloc_args(data);
		init_args(data);
		execve(data->path, data->args, data->env);
		close(pipe_sio[0]);
		exit(0);
	}
	close(pipe_sio[1]);
	close(pipe_sio[0]);
	waitpid(pid2, NULL, 0);
}

void	execute_search_in_out(t_data *data)
{
	//printf("hereee11\n");
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
		execute_command_search_in_out(data);
}
