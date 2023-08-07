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

	i = 0;
	while (data->export_var[i])
	{
		if (ft_strcmp_unset(data->token[data->token_y + 1],
				data->export_var[i]) == 1)
		{
			reset_var(data->export_var[i]);
			return ;
		}
		i++;
	}
}
