/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 08:44:15 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 08:44:16 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

int	ft_strcmp3(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i + 1] != '\0')
		{
			if (s2[i] == '\0')
			{
				return (s1[i] - s2[i]);
			}
			else
			{
				i++;
			}
			if (s1[i + 1] == '\0' && s2[i] == '\0')
				return (0);
		}
	}
	return (s1[i] - s2[i]);
}

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] != '\0')
		{
			if (s2[i] == '\0')
				return (s1[i] - s2[i]);
			else
				i++;
		}
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
	}
	if (s1[i] == ' ')
		return (0);
	return (s1[i] - s2[i]);
}

void	init_args(t_data *data)
{
	int	y;
	int	i_args;

	i_args = 1;
	y = data->token_y + 1;
	data->args[0] = data->path;
	while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
	{
		data->args[i_args] = data->token[y];
		i_args++;
		y++;
	}
}
