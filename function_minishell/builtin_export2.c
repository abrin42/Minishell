#include "../minishell.h"

void    init_export_var(t_data *data)
{
    int i;

    i = 0;
    data->export_var = malloc(sizeof(char *) * 1000);
}

int	ft_strcmp_export_var(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] != '\0')
		{
			if (s2[i] == '\0')
				return (s1[i] - s2[i]);
			else
				i++;
		}
		if (s1[i] == '\0')
			return (0);
		else if (s1[i] == '=' && s2[i] == '=')
			return (1);
	}
	return (s1[i] - s2[i]);
}

void    reset_var(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        str[i] = '\0';
        i++;
    }
}

int	ft_strcmp_unset(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] != '\0')
		{
			if (s2[i] == '\0')
				return (s1[i] - s2[i]);
			else
				i++;
		}
	}
	if (s2[i] == '=' && s1[i] == '\0')
		return (1);
	return (s1[i] - s2[i]);
}

void    ft_unset(t_data *data)
{
    int i;

    i = 0;
    while(data->export_var[i])
    {
        if (ft_strcmp_unset(data->token[data->token_y + 1], data->export_var[i]) == 1)
        {
            reset_var(data->export_var[i]);
            return ;
        }
        i++;
    }
}