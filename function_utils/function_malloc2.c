#include "../minishell.h"

void	ft_get_path(t_data *data, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (data->export_var[i][j] != '\0')
		j++;
	gc_malloc(&data->gc, sizeof(char) * j);
	j = 0;
	while (data->export_var[i][j] != '=')
		j++;
	while (data->export_var[i][j] != '\0')
	{
		data->path_temp[k] = data->export_var[i][j];
		k++;
		j++;
	}
	data->path_temp[k] = '\0';
}

void	ft_getenv_path(t_data *data)
{
	int	i;

	i = 0;
	while (data->export_var[i])
	{
		if (ft_strcmp_export_var(data->export_var[i], "PATH=") == 1)
		{
			ft_get_path(data, i);
			return ;
		}
		i++;
	}
	data->path_temp = NULL;
}
