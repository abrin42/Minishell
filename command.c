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
    chdir(data->parsing[1]);
}

void    ft_env(t_data *data)
{
    int i;

    i = 0;
    while (data->env[i])
        printf("%s\n", data->env[i++]);
}

int command_terminal (t_data *data)
{
    char    **args;
    char    *path;
    int     i;
    int     stop_condition;
    int status;
    __pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        //perror("fork");
        //bash: fork : no such file 
        // put_error(strerror(errno), file)
        write (2, "Erreur lors de la création du processus.\n", 41); // demander a noah si la sortie 2 c'est good  
        //printf("Erreur lors de la création du processus.\n");
        return (0);
    }
    else if (pid == 0)
    {
        args = malloc_args(data, args);
        malloc_bdd(data);
        i = 0;
        while (data->bdd[i] != NULL)
        {
            stop_condition = 0;
            path = ft_strjoin(data->bdd[i], data->parsing[0]); //attention data->parsing[0] echo | ls = ls
            stop_condition = execve(path, args, data->env);
            free(path);
            i++;
        }
    }
    waitpid(pid, &status, 0);
    if (stop_condition != -1)
        return (1);
    return (0);
}