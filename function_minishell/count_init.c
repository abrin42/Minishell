/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_variable_export.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 05:28:56 by abrin             #+#    #+#             */
/*   Updated: 2023/08/06 05:28:58 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_bin(t_data *data)
{
	char	*new;
	char	*new1;

	new = ft_strjoin3("/bin/", data->buffer, data, data->p);
	new1 = ft_strjoin3("/bin/", data->buffer, data, data->p);
	if (ft_strcmp(data->buffer, new) != 0)
	{
		free(new);
		free(new1);
		return (1);
	}
	if (ft_strcmp(data->buffer, new) != 0)
	{
		free(new);
		free(new1);
		return (1);
	}
	free(new);
	free(new1);
	return (0);
}

void	count_pipe_redirect(t_data *data)
{
	if (data->buffer[data->i] == '>')
		data->count_redirect++;
	else if (data->buffer[data->i] == '<')
		data->count_redirect++;
	else if (data->buffer[data->i] == '|')
		data->count_pipe2++;
}

void	init_count_pipe_redirect(t_data *data)
{
	data->count_pipe2 = 0;
	data->count_redirect = 0;
}

void	count_pipe(t_data *data)
{
	int	i;

	i = 0;
	data->count_pipe = 0;
	while (data->token[i][0] != '\0')
	{
		if (data->token[i][0] == '|')
			data->count_pipe++;
		i++;
	}
}
