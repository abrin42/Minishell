#include "minishell.h"

void    ft_echo(t_data *data, int i)
{
    while (data->line[i])
    {
        write(1, &data->line[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

void    ft_pwd(t_data *data)
{
    data->pwd = getenv("PWD");
    printf("%s\n", data->pwd);
}