/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:20:04 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 01:54:35 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_path(char *path_temp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (path_temp[i] != '\0')
	{
		if (path_temp[i] == ':')
			count++;
		i++;
	}
	count++;
	return (count);
}

void	malloc_path_bdd1(t_data *data)
{
	data->i_bdd = 0;
	data->x_bdd = 0;
	data->y_bdd = 0;
	ft_getenv_path(data);
	if (data->path_temp == NULL)
		return ;
	data->count_path = count_path(data->path_temp);
	data->path_bdd = gc_malloc(&data->gc, sizeof(char *) * data->count_path);
	while (data->count_path > 0)
	{
		data->x_bdd = 0;
		while (data->path_temp[data->i_bdd] != ':'
			&& data->path_temp[data->i_bdd] != '\0')
		{
			data->x_bdd++;
			data->i_bdd++;
		}
		data->path_bdd[data->y_bdd] = gc_malloc
			(&data->gc, sizeof(char) * (data->x_bdd + 2));
		data->y_bdd++;
		data->i_bdd++;
		data->count_path--;
	}
}

int	malloc_path_bdd(t_data *data)
{
	malloc_path_bdd1(data);
	if (command_exist_builtin(data) == 0)
		return (0);
	else if (data->path_temp == NULL)
		return (1);
	data->count_path = count_path(data->path_temp);
	data->y_bdd = 0;
	data->i_bdd = 0;
	while (data->count_path > 0)
	{
		data->x_bdd = 0;
		while (data->path_temp[data->i_bdd] != ':'
			&& data->path_temp[data->i_bdd] != '\0')
		{
			data->path_bdd[data->y_bdd][data->x_bdd++] = data->path_temp
			[data->i_bdd++];
		}
		data->path_bdd[data->y_bdd][data->x_bdd] = '/';
		data->path_bdd[data->y_bdd][data->x_bdd + 1] = '\0';
		data->y_bdd++;
		data->i_bdd++;
		data->count_path--;
	}
	return (0);
}

void	malloc_data(t_data *data)
{
	int	i;

	gc_init(&data->gc);
	data->token = gc_malloc(&data->gc, sizeof(char *) * 100);
	i = 0;
	while (i <= 100)
	{
		data->token[i] = gc_malloc(&data->gc, sizeof(char) * 1000);
		data->token[i][0] = '\0';
		i++;
	}
}

void	malloc_args(t_data *data)
{
	int	y;

	y = 0;
	while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
		y++;
	data->args = gc_malloc(&data->gc, sizeof(char *) * y + 1);
	y = 0;
	while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
	{
		data->args[y] = gc_malloc(&data->gc, sizeof(char *) * 10000);
		y++;
	}
}
