/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 06:26:02 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 03:44:53 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	search_in_file2(t_data *data, int y)
{
	pid_t	pid;

	while (data->token[y][0] != '<')
		y--;
	pipe(data->tube_search);
	pid = fork();
	if (pid == 0)
	{
		search_in_file1(data);
		exit(0);
	}
	close(data->tube_search[1]);
	waitpid(pid, NULL, 0);
}

int	search_in_file(t_data *data, int y)
{
	init_search_in_file(data);
	while (data->token[y][0] != '|' && data->token[y][0] != '\0')
	{
		while (data->token[y][0] != '<' && data->token[y][0] != '|'
			&& data->token[y][0] != '\0')
			y++;
		if (data->token[y][0] == '\0' || data->token[y][0] == '|')
			break ;
		y++;
		data->fd1 = open(data->token[y], O_RDONLY);
		if (data->fd1 == -1)
		{
			perror(data->token[data->token_y + 2]);
			data->error = 1;
			return (-1);
		}
	}
	search_in_file2(data, y);
	return (0);
}
