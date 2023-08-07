/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 05:25:32 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 05:25:33 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_exist_builtin(t_data *data)
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
	else
		return (-1);
}

int	command_exist(t_data *data)
{
	if (command_exist_builtin(data) == 0)
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
