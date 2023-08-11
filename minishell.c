/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrin <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:35:21 by abrin             #+#    #+#             */
/*   Updated: 2023/08/06 19:35:23 by abrin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_data *data)
{
	data->pipe_not_close = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		data->buffer = readline("\033[0;34m#Minishell ➤ \033[0m");
		if (data->buffer == NULL)
			break ;
		while (ft_iswhitespace(data->buffer[0]) == 1)
			data->buffer++;
		prompt2(data);
	}
	rl_clear_history();
	free(data->buffer);
	gc_clean(&data->gc);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*shlvl_str;

	malloc_data(&data);
	init_data(&data);
	data.error = 0;
	init_export_var(&data);
	data.env = envp;
	shlvl_str = getenv("SHLVL");
	shlvl_str[0] += 1;
	setenv("SHLVL", shlvl_str, 1);
	data.export = envp;
	prompt(&data);
}
