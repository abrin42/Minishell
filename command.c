#include "minishell.h"

void    ft_echo(t_data *data, int i)
{
    ft_putstr(data->parsing[data->parsing_y + 1]);
    //printf("%s\n", data->parsing[data->parsing_y + 1]);
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

    args = malloc(sizeof (char*) * 2);
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
        //args = malloc_args(data, args);
        //malloc_bdd(data);
        i = 0;
        while (data->bdd[i] != NULL )
        {
            stop_condition = 0;
            path = ft_strjoin(data->bdd[i], data->parsing[data->parsing_y]); //attention data->parsing[0] echo | ls = ls
            args[0] = ft_strdup(path);
            //args[1] = ft_strdup(data->parsing[data->parsing_y + 1]);
            //if (!(data->parsing[data->parsing_y + 1][0]))
                args[1] = NULL;
            int x = 0;
            stop_condition = execve(path, args, data->env);
            //free(path);
            //free(args[0]);
            //free(args[1]);
            i++;
        }
    }
    waitpid(pid, &status, 0);
    if (stop_condition != -1)
        return (1);
    return (0);
}