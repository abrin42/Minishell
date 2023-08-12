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

void	ft_echo_n(t_data *data)
{
	ft_echo_n_init(data);
	while (data->token[data->token_y][0] == '-')
	{
		data->i_echo = 1;
		if (data->token[data->token_y][0] == '-')
		{
			ft_echo_n1(data);
			if (data->token[data->token_y][data->i_echo] == '\0')
			{
				data->token_y++;
				if (data->token[data->token_y][0] != '-')
				{
					data->echo_n = 0;
					return ;
				}
			}
			else
			{
				data->token_y++;
				if (data->token[data->token_y][0] == '-')
					break ;
			}
		}
	}
	data->token_y--;
	if (data->trace_echo > 1)
	{
		data->echo_n = 0;
		return ;
	}
	ft_echo_n2(data);
}

void	ft_unset(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->export_var[i])
	{
		if (ft_strcmp_unset(data->token[data->token_y + 1],
				data->export_var[i]) == 1 && ft_strcmp(data->token
				[data->token_y + 1], "PATH") == 0)
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
