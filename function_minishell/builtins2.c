/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 07:32:47 by abrin             #+#    #+#             */
/*   Updated: 2023/08/07 07:32:48 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->export_var[i])
	{
		if (ft_strcmp_unset(data->token[data->token_y + 1],
				data->export_var[i]) == 1 && ft_strcmp(data->token[data->token_y + 1], "PATH") == 0)
		{
			data->export_var[i] = "PATH=NULL";
			return ;
		}
		else if (ft_strcmp_unset(data->token[data->token_y + 1],
				data->export_var[i]) == 1)
		{
			reset_var(data->export_var[i]);
			return ;
		}
		i++;
	}
}
