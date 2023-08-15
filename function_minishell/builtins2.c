/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 07:32:47 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 02:35:41 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo_n_return(t_data *data)
{
	if (data->trace_echo > 1)
	{
		data->echo_n = 0;
		return (1);
	}
	return (-1);
}

void	ft_echo_n(t_data *data)
{
	int	n;

	n = 0;
	ft_echo_n_init(data);
	while (data->token[data->token_y][0] == '-')
	{
		data->i_echo = 1;
		if (data->token[data->token_y][0] == '-')
		{
			n = ft_echo_n1(data);
			if (data->token[data->token_y][data->i_echo] == '\0')
			{
				if (ft_echo_n_if(data) == 1 && n != 0)
					return ;
			}
			else
				if (ft_echo_n_if2(data) == 1)
					break ;
		}
	}
	data->token_y--;
	if (ft_echo_n_return(data) == 1)
		return ;
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

char	*ft_strdup(const char *s, t_data *data)
{
	int		i;
	int		j;
	char	*dest;

	i = ft_strlen((char *)s);
	j = 0;
	dest = (char *)gc_malloc(&data->gc, sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}
