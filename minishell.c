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

int condition_error = 0;

int	exit_final(t_data *data)
{
	if (ft_strcmp(data->token[data->token_y], "exit") == 0
		&& data->token[data->token_y + 1][0] != '\0')
	{
		if (ft_isalpha_str(data->token[data->token_y + 1]) == 0
			&& ft_atoi(data->token[data->token_y + 1]) > 255)
			return (255);
		else if (ft_isalpha_str(data->token[data->token_y + 1]) == 0)
			return (ft_atoi(data->token[data->token_y + 1]));
		else
		{
			printf("exit: %s: numeric argument required",
				data->token[data->token_y + 1]);
			return (2);
		}
	}
	printf("\n");
	return (0);
}

void	prompt(t_data *data)
{
	int	error_exit;

	error_exit = -1;
	data->pipe_not_close = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (42)
	{
		condition_error = 0;
		if (data->buffer == NULL && data->i_buffer == 2000000)
			break ;
		data->buffer = readline("\033[0;34m#Minishell ➤ \033[0m");
		if (data->buffer == NULL)
			break ;
		while (ft_iswhitespace(data->buffer[0]) == 1)
			data->buffer++;
		prompt2(data);
	}
	error_exit = exit_final(data);
	rl_clear_history();
	free(data->buffer);
	gc_clean(&data->gc);
	if (error_exit != -1)
		exit(error_exit);
}

void	ft_getenv_shlvl(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->export_var[i])
	{
		if (ft_strcmp_export_var(data->export_var[i], "SHLVL=") == 1)
		{
			j = 0;
			while (data->export_var[i][j] != '='
				&& data->export_var[i][j] != '\0')
				j++;
			j++;
			data->export_var[i][j] += 1;
			return ;
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*shlvl_str;

	malloc_data(&data);
	init_data(&data);
	data.error = 0;
	data.env = envp;
	init_export_var(&data);
	ft_getenv_shlvl(&data);
	data.export = envp;
	data.buffer = NULL;
	prompt(&data);
}
