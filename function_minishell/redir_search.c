/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 06:26:02 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 06:26:03 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
