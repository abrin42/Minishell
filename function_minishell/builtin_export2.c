/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 05:13:21 by abrin             #+#    #+#             */
/*   Updated: 2023/08/06 05:13:23 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_export_var(t_data *data)
{
	int	i;

	i = 0;
	data->export_var = gc_malloc(&data->gc, sizeof(char *) * 1000);
	while (data->env[i])
	{
		data->export_var[i] = data->env[i];
		i++;
	}
}

int	ft_strcmp_export_var(char *s1, char *s2)
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
		if (s1[i] == '\0')
			return (0);
		else if (s1[i] == '=' && s2[i] == '=')
			return (1);
	}
	return (-1);
}

void	reset_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
}

int	ft_strcmp_unset(char *s1, char *s2)
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
	}
	if (s2[i] == '=' && s1[i] == '\0')
		return (1);
	return (s1[i] - s2[i]);
}
