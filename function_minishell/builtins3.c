/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:04:35 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 02:21:30 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_n1(t_data *data)
{
	int	n;

	n = 0;
	data->trace_echo++;
	while (data->token[data->token_y][data->i_echo]
		&& (data->token[data->token_y][data->i_echo] == 'n'
		|| data->token[data->token_y][data->i_echo] == 92))
	{
		if (data->token[data->token_y][data->i_echo] == 'n')
			n++;
		data->i_echo++;
	}
	return (n);
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
