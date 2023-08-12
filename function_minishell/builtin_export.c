/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 05:10:06 by abrin             #+#    #+#             */
/*   Updated: 2023/08/06 05:10:09 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_result_export_var(t_data *data, int i)
{
	int		y;
	char	temp;

	y = 0;
	while (data->export_var[i][y] != '=' && data->export_var[i][y] != '\0')
		y++;
	if (data->export_var[i][y] == '=')
	{
		while (data->export_var[i][y])
			y++;
		data->export_var[i][y + 2] = '\0';
		data->export_var[i][y + 1] = '"';
		while (data->export_var[i][y] != '=')
		{
			data->export_var[i][y] = data->export_var[i][y - 1];
			y--;
		}
		y++;
		data->export_var[i][y] = '"';
	}
	else
		clean_result_export_var2(data, i, y);
}

void	tri_export(t_data *data)
{
	int		i;
	int		y;
	char	*temp;

	i = 0;
	y = 0;
	temp = malloc(sizeof(char) * 1000);
	while (data->export[i + 1])
	{
		y = i + 1;
		if (data->export[i][0] > data->export[y][0])
		{
			temp = data->export[i];
			data->export[i] = data->export[y];
			data->export[y] = temp;
			i = 0;
		}
		i++;
	}
	temp = NULL;
	free(temp);
}

void	tri_export_var(t_data *data)
{
	int		i;
	int		y;
	char	*temp;

	i = 0;
	y = 0;
	temp = malloc(sizeof(char) * 1000);
	while (data->export_var[i + 1])
	{
		y = i + 1;
		if (data->export_var[i][0] > data->export_var[y][0])
		{
			temp = data->export_var[i];
			data->export_var[i] = data->export_var[y];
			data->export_var[y] = temp;
			i = 0;
		}
		i++;
	}
	temp = NULL;
	free(temp);
}

void	ft_export2(t_data *data, int i)
{
	tri_export_var(data);
	i = 0;
	while (data->export_var[i])
	{
		if (data->export_var[i][0] != '\0')
			printf("declare -x %s\n", data->export_var[i]);
		i++;
	}
}

void	ft_export(t_data *data)
{
	int	i;

	i = 0;
	if (data->token[data->token_y + 1][0] != '\0')
	{
		while (data->export_var[i])
		{
			if (ft_strcmp_export_var(data->token[data->token_y + 1],
					data->export_var[i]) == 0)
				return ;
			else if (ft_strcmp_export_var(data->token[data->token_y + 1],
					data->export_var[i]) == 1)
				break ;
			i++;
		}
		data->export_var[i] = ft_strdup_special(data->token[data->token_y + 1]);
		clean_result_export_var(data, i);
	}
	else
		ft_export2(data, i);
}
