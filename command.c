#include "minishell.h"

void    ft_echo(t_data *data, int i)
{
    printf("%s\n", data->parsing[1]);
}

void    ft_pwd(t_data *data)
{
    char    *str;
    char    *pwd;

    str = malloc(sizeof(char) * 500);
    pwd = malloc(sizeof(char) * 500);
    str = NULL;
    pwd = NULL;
    pwd = getcwd(str, 100);
    printf("%s\n", pwd);
    free(str);
    free(pwd);
}

void ft_cd(t_data *data)
{
    //data->parsing[1] = "..";
    chdir(data->parsing[1]);
}

void    ft_env(t_data *data)
{
    int i;

    i = 0;
    while (data->env[i])
        printf("%s\n", data->env[i++]);
}