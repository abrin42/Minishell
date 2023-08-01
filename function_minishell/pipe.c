#include "../minishell.h"

void last_command_pipe(t_data *data)
{
    int     i;
    pid_t pid;

    malloc_args(data);
    init_args(data);
    pid = fork();
    if (pid == 0)
    {
        close(data->tube[1]);
        dup2(data->tube[0], 0);
        execve(data->path, data->args, data->env);
        close(data->tube[0]);
        exit (0);
    }
    else
    {
        close(data->tube[0]);
        waitpid(pid, NULL, 0);
        close(data->tube[1]);
    }
}

void command_pipe(t_data *data)
{
    int     i;
    pid_t pid;

    malloc_args(data);
    init_args(data);
    pid = fork();
    if (pid == 0)
    {
        //close(data->tube[1]);
        dup2(data->tube[0], 0);
        pipe(data->tube);
        dup2(data->tube[1], 1);
        execve(data->path, data->args, data->env);
        //close(data->tube[0]);
        exit (0);
    }
    else
    {
        //close(data->tube[1]);
        waitpid(pid, NULL, 0);
        //close(data->tube[0]);
    }
}

void first_command_pipe(t_data *data)
{
    int     i;
    pid_t pid;

    malloc_args(data);
    init_args(data);
    data->condition = 0;
    pipe(data->tube);
    pid = fork();
    if (pid == 0)
    {
        close(data->tube[0]);
        dup2(data->tube[1], 1);
        execve(data->path, data->args, data->env);
        exit (0);
    }
    else
    {
        close(data->tube[1]);
        waitpid(pid, NULL, 0);
    }
}

/*EXEMPLE DE PIPE
void    execute_command_pipe(t_data *data)
{
    int     i;
    pid_t pid;

    malloc_args(data);
    pipe(data->tube);
    pid = fork();
    if (pid == 0)
    {
        init_args(data);
        close(data->tube[0]);
        if (data->count_pipe != 0 && data->condition == 1)
        {
            printf("DUP 1\n");
            dup2(data->tube[1], STDOUT_FILENO);
        }
        else if (data->count_pipe != 0)
        {
            printf("DUP 2\n");
            dup2(data->tube[1], STDOUT_FILENO);
        }
        else if (data->count_pipe == 0)
        {
            printf("DUP 3\n");
            dup2(data->tube[0], STDIN_FILENO);
        }
        //execlp("ls", "ls", NULL);
        execve(data->path, data->args, data->env);
    }
    else
    {
        waitpid(pid, NULL, 0);
        init_args(data);
        close(data->tube[1]);
        pid = fork();
        if (pid == 0)
        {
            dup2(data->tube[0], STDIN_FILENO);
            //execlp("wc", "wc", NULL);
            execve(data->path, data->args, data->env);
        }
        else
        {
            waitpid(pid, NULL, 0);
            close(data->tube[0]);
        }
    }
}*/

/*
for (size_t p = 0; p < 10; p++)
{
    printf("ICI ARGS ===%s===\n", data->args[p]);
    p++;
}*/