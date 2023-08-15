/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarie <tmarie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 05:13:31 by abrin             #+#    #+#             */
/*   Updated: 2023/08/15 02:20:39 by tmarie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_data *data)
{
	int	condition;

	condition = 0;
	data->token_y++;
	ft_echo_n(data);
	if (data->echo_n == 0)
		condition = 1;
	else if (ft_strcmp(data->token[data->token_y], "$?") == 0)
	{
		printf("%d\n", data->error);
		data->error = 0;
		return ;
	}
	while ((data->token[data->token_y][0] != '\0'
		&& !ft_is_operator(data->token[data->token_y][0]))
		|| (data->token[data->token_y + 1][0] != '\0'
		&& !ft_is_operator(data->token[data->token_y + 1][0])
		&& !ft_is_operator(data->token[data->token_y][0])))
	{
		ft_putstr(data->token[data->token_y]);
		write(1, " ", 1);
		data->token_y++;
	}
	if (condition == 0)
		write(1, "\n", 1);
}

void	ft_pwd(t_data *data)
{
	char	*pwd;

	pwd = gc_malloc(&data->gc, sizeof(char) * 1024);
	getcwd(pwd, 1024);
	ft_putstr(pwd);
	ft_putchar('\n');
}

void	ft_cd(t_data *data)
{
	int	error;

	error = 0;
	data->token_y++;
	if (data->token[data->token_y][0] == '\0')
	{
		printf("Not enough arguments for cd\n");
		return ;
	}
	if (!ft_is_operator(data->token[data->token_y + 1][0])
		&& data->token[data->token_y + 1][0] != '\0')
	{
		printf("Too many arguments for cd\n");
		return ;
	}
	error = chdir(data->token[data->token_y]);
	if (error == -1)
	{
		data->error = 1;
		printf("cd: %s: No such file or directory\n",
			data->token[data->token_y]);
	}
}

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->export_var[i])
	{
		if (data->export_var[i])
			printf("%s\n", data->export_var[i]);
		i++;
	}
}

void	ft_exit(t_data *data)
{
	if (ft_isdigit(data->token[data->token_y + 1][0]) == 1
		&& data->token[data->token_y + 2][0] != '\0')
	{
		printf("Too many arguments for exit\n");
		return ;
	}
	printf("exit");
	data->i_buffer = 2000000;
	data->buffer = NULL;
}
