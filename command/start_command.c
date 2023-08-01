#include "../minishell.h"

int command_exist(t_data *data)
{
    if (ft_strcmp(data->token[data->token_y] , "echo") == 0)
        return (0);
    else if (ft_strcmp(data->token[data->token_y] , "cd") == 0)
        return (0);
    else if (ft_strcmp(data->token[data->token_y] , "pwd") == 0)
        return (0);
    else if (ft_strcmp(data->token[data->token_y] , "env") == 0)
        return (0);
    else if (ft_strcmp(data->token[data->token_y] , "export") == 0)
        return (0);
    else if (ft_strcmp(data->token[data->token_y] , "unset") == 0)
        return (0);
    else if (ft_strcmp(data->token[data->token_y] , "exit") == 0)
        return (0);
    else
    {
        data->count_path = count_path(getenv("PATH"));
        while (data->count_path > 0)
        {
            data->path = ft_strjoin(data->path_bdd[data->count_path - 1], data->token[data->token_y], data);
            if (access(data->path, X_OK) == 0)
                return(1);
            data->count_path--;
        }
    }
    return (-1);
}

void    execute_bultins(t_data *data)
{
    if (ft_strcmp(data->token[data->token_y] , "echo") == 0)
        ft_echo(data);
    if (ft_strcmp(data->token[data->token_y] , "cd") == 0)
        ft_cd(data);
    else if (ft_strcmp(data->token[data->token_y] , "pwd") == 0)
        ft_pwd(data);
    else if (ft_strcmp(data->token[data->token_y] , "env") == 0)
        ft_env(data);
    else if (ft_strcmp(data->token[data->token_y] , "export") == 0)
        ft_export(data);
    else if (ft_strcmp(data->token[data->token_y] , "unset") == 0)
        ft_unset(data);
    else if (ft_strcmp(data->token[data->token_y] , "exit") == 0)
        ft_exit(data);
}

void    execute_command(t_data *data)
{
    int     i;
    int status;
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        malloc_args(data);
        init_args(data);
        execve(data->path, data->args, data->env);
        exit(0);
    }
    waitpid(pid, &status, 0);
}

void start_command(t_data *data)
{
    data->token_x = 0;
    data->token_y = 0;
    data->condition = 1;
    malloc_path_bdd(data);
    execute_cmd(data, 0)
    //hereeeeeeeeeeeeeeeeeee debut comande 
}