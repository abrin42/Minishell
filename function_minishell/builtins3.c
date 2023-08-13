/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:04:35 by abrin             #+#    #+#             */
/*   Updated: 2023/08/13 17:04:37 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo_n1(t_data *data)
{
	data->trace_echo++;
	while (data->token[data->token_y][data->i_echo]
		&& data->token[data->token_y][data->i_echo] == 'n')
		data->i_echo++;
}

void	ft_echo_n2(t_data *data)
{
	if (data->trace_echo == 1)
		data->token_y--;
	data->token_y++;
	data->echo_n = 2;
}

void	ft_echo_n_init(t_data *data)
{
	data->echo_n = 1;
	data->trace_echo = 0;
	data->i_echo = 1;
}

int	ft_echo_n_if(t_data *data)
{
	data->token_y++;
	if (data->token[data->token_y][0] != '-')
	{
		data->echo_n = 0;
		return (1);
	}
	return (0);
}

int	ft_echo_n_if2(t_data *data)
{
	data->token_y++;
	if (data->token[data->token_y][0] == '-')
		return (1);
	return (0);
}
