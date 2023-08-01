#include "../minishell.h"

char	*ft_strdup_special(const char *src)
{
	char	*new;
	int		i;

	i = 0;
	while (src[i])
		i++;
	if (!(new = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (src[i] && src[i] != ' ')
	{
		new[i] = src[i];
		i++;
	}
	while (src[i])
	{
		new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	clean_result_export_var(t_data *data, int i)
{
	int	y;
	char	temp;
	
	y = 0;
	while (data->export_var[i][y] != '=' && data->export_var[i][y] != '\0')
		y++;
	if (data->export_var[i][y] == '=')
	{
		while(data->export_var[i][y])
			y++;
		data->export_var[i][y + 2] = '\0';
		data->export_var[i][y + 1] = '"';
		while(data->export_var[i][y] != '=')
		{
			data->export_var[i][y] = data->export_var[i][y - 1];
			y--;
		}
		y++;
		data->export_var[i][y] = '"';
	}
	else
	{
		data->export_var[i][y] = '=';
		data->export_var[i][y + 1] = '\'';
		data->export_var[i][y + 2] = '\'';
		data->export_var[i][y + 3] = '\0';
	}
}

void    tri_export(t_data *data)
{
    int i;
    int y;
    char *temp;

    i = 0;
    y = 0;
    temp = malloc(sizeof(char) * 1000);
    while (data->export[i + 1])
    {
        y = i + 1;
        if (data->export[i][0] > data->export[y][0])
        {
            temp = data->export[i];
            data->export[i] = data->export[y];
            data->export[y] = temp;
            i = 0;
        }
        i++;
    }
    temp = NULL;
    free(temp);
}

void    tri_export_var(t_data *data)
{
    int i;
    int y;
    char *temp;

    i = 0;
    y = 0;
    temp = malloc(sizeof(char) * 1000);
    while (data->export_var[i + 1])
    {
        y = i + 1;
        if (data->export_var[i][0] > data->export_var[y][0])
        {
            temp = data->export_var[i];
            data->export_var[i] = data->export_var[y];
            data->export_var[y] = temp;
            i = 0;
        }
        i++;
    }
    temp = NULL;
    free(temp);
}

void    ft_export(t_data *data)
{
    int    i;

    i = 0;
    if (data->token[data->token_y + 1][0] != '\0')
    {
        while (data->export_var[i])
        {
        	if (ft_strcmp_export_var(data->token[data->token_y + 1], data->export_var[i]) == 0)
        		return ;
        	else if(ft_strcmp_export_var(data->token[data->token_y + 1], data->export_var[i]) == 1)
        		break ;
            i++;
        }
        data->export_var[i] = ft_strdup_special(data->token[data->token_y + 1]);
        clean_result_export_var(data, i);
    }
    else
    {
        tri_export(data);
        tri_export_var(data);
        i = 0;
        while (data->export[i])
            printf("declare -x %s\n", data->export[i++]);
        i = 0;
        while (data->export_var[i])
        {
            if (data->export_var[i][0] != '\0')
                printf("declare -x %s\n", data->export_var[i]);
            i++;
        }
    }
}