/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 07:58:55 by abrin             #+#    #+#             */
/*   Updated: 2023/08/11 07:58:56 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	other_prompt2(t_data *data)
{
	add_history(data->buffer);
	data->buffer = clean_buffer(data);
	fill_token(data);
	data->pipe_not_close--;
}
