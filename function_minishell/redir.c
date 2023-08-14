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
	y = open_in_file_pipe(data, y);
	redirection_in_file(data, y);
	close(data->tube_redirect[0]);
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
	{
		if (data->token[y][1] == '<')
			return (2);
		return (0);
	}
	return (1);
}
