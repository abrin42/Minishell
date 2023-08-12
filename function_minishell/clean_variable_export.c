/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_variable_export.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 05:29:03 by abrin             #+#    #+#             */
/*   Updated: 2023/08/06 05:29:04 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_var(const char *src, int i, t_data *data)
{
	char	*new;
	int		size;

	size = i;
	while (src[size] != '\0' && src[size] != ' ' && src[i] && src[i] != '"')
		size++;
	new = gc_malloc(&data->gc, sizeof(char) * (size + 1));
	size = 0;
	while (src[i] && src[i] != ' ' && src[i] && src[i] != '"')
	{
		new[size] = src[i];
		i++;
		size++;
	}
	new[size] = '\0';
	return (new);
}

int	ft_strcmp_var(char *var, char *export_var, t_data *data)
{
	data->i_var = 0;
	while (export_var[data->i_var] == var[data->i_var])
		data->i_var++;
	if (export_var[data->i_var] == '=' && var[data->i_var] == '\0')
		return (-2);
	else
		return (-1);
}

void	change_by_var(t_data *data, char *new_line, int k)
{
	data->i_var = 0;
	while (data->export_var[k][data->i_var] != '\''
		&& data->export_var[k][data->i_var] != '"'
		&& data->export_var[k][data->i_var] != '\0'
		&& data->export_var[k][data->i_var] != '=')
		data->i_var++;
	if (data->export_var[k][data->i_var + 1] == '\''
		|| data->export_var[k][data->i_var + 1] == '"')
		data->i_var += 2;
	else
		data->i_var++;
	while (data->export_var[k][data->i_var] != '\''
		&& data->export_var[k][data->i_var] != '"'
		&& data->export_var[k][data->i_var] != '\0')
		new_line[data->i_new_line++] = data->export_var[k][data->i_var++];
	while (data->buffer[data->i_buffer] != '\0' && data->buffer
		[data->i_buffer] != ' ' && data->buffer[data->i_buffer] != '"')
	{
		new_line[data->i_new_line++] = ' ';
		data->i_buffer++;
	}
}

void	clean_var(t_data *data, char *new_line)
{
	int		condition;

	data->var = ft_strdup_var(data->buffer, data->i_buffer + 1, data);
	data->k = 0;
	condition = 0;
	while (data->export_var[data->k])
	{
		if (ft_strcmp_var(data->var, data->export_var[data->k], data) == -2)
		{
			condition = -2;
			break ;
		}
		data->k++;
	}
	if (condition == -2)
		change_by_var(data, new_line, data->k);
	else
	{
		while (data->buffer[data->i_buffer] != '"' && data->buffer
			[data->i_buffer] != ' ' && data->buffer[data->i_buffer] != '\0')
		{
			new_line[data->i_new_line++] = ' ';
			data->i_buffer++;
		}
	}
}
