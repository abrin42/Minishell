#include "minishell.h"

void    ft_echo(t_data *data, int i)
{
        write(1, &data->parsing[data->parsing_y], ft_strlen(data->parsing[1]));
    write(1, "\n", 1);
}

void    ft_pwd(t_data *data)
{
    data->pwd = getenv("PWD");
    printf("%s\n", data->pwd);
}

void ft_cd(t_data *data)
{

}