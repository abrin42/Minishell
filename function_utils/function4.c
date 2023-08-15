/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 08:44:15 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 01:54:11 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int	i;

	i_args = 1;
	y = data->token_y + 1;
	i = 0;
	data->args[0] = data->path;
	while (i < y)
	{
		data->args[i_args] = NULL;
		i++;
	}
	while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
	{
		data->args[i_args] = data->token[y];
		i_args++;
		y++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_iswhitespace(nptr[i]) && nptr[i] != '\0')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i] != '\0')
	{
		result = result * 10 + nptr[i] - '0';
		i++;
	}
	return (result * sign);
}
