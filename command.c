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

/*void    free_args(char **args, t_data *data)
{
        while (data->i_args < 11)
        {
            free(args[data->i_args]);
            data->i_args++;
        }
        free(args);
        return ;
}

void    ft_terminal(t_data *data)
{
    __pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        printf("Erreur lors de la création du processus.\n");
        return ;
    }
    else if (pid == 0)
    {
        char **args;

        data->i_args = 10;
        args = malloc(sizeof(char *) * data->i_args);
        while (data->i_args > -1)
        {
            args[data->i_args] = malloc(sizeof(char) * 10);
            data->i_args--;
        }
        args[0] = data->parsing[0];
        args[1] = NULL;
        execve("/bin/ls", args, data->env);
        free_args(args, data);
    }
    waitpid(pid, &status, 0);
    return ;
}*/

int verif_command (t_data *data)
{
    char    **args;
    char    *path;
    int     i;
    int status;
    __pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        printf("Erreur lors de la création du processus.\n");
        return (0);
    }
    else if (pid == 0)
    {
        args = malloc_args(data, args);
        malloc_bdd(data);
        i = 0;
        while (data->bdd[i] != NULL)
        {
            path = ft_strjoin(data->bdd[i], data->parsing[0]);
            execve(path, args, data->env);
            free(path);
            i++;
        }
    }
    waitpid(pid, &status, 0);
    return (0);
}