/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 05:37:32 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 05:37:34 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_special(const char *src)
{
	char	*new;
	int		i;

	i = 0;
	while (src[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != ' ')
	{
		new[i] = src[i];
		i++;
	}
	while (src[i])
	{
		new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	clean_result_export_var2(t_data *data, int i, int y)
{
	data->export_var[i][y] = '=';
	data->export_var[i][y + 1] = '\'';
	data->export_var[i][y + 2] = '\'';
	data->export_var[i][y + 3] = '\0';
}
