/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 05:13:21 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 00:43:51 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
