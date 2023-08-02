#include "../minishell.h"

/*
for (size_t p = 0; p < 10; p++)
{
    printf("ICI ARGS ===%s===\n", data->args[p]);
    p++;
}*/

void pipe_end(t_data *data, int *fd_pipe)
{
    printf("ICI END\n");
    pid_t pid = fork();
    int status_pid;
    if (pid == 0)
    {
        close(fd_pipe[1]);
        dup2(fd_pipe[0], STDIN_FILENO);
        if (command_exist(data) == 0 || command_exist(data) == 1)
            execute(data);
        exit(0);
    }
    close(fd_pipe[0]);
    waitpid(pid, &status_pid, 0);
}

void pipe_middle(t_data *data, int *fd_pipe_in, int *fd_pipe_out)
{
        printf("ICI MIDDLE\n");
    int status_pid;
    pid_t pid = fork();
    if (pid == 0)
    {
        close(fd_pipe_in[1]);
        close(fd_pipe_out[0]);
        dup2(fd_pipe_in[0], STDIN_FILENO);
        dup2(fd_pipe_out[1], STDOUT_FILENO);
        if (command_exist(data) == 0 || command_exist(data) == 1)
            execute(data);
        exit(0);
    }
    close(fd_pipe_in[0]);
    close(fd_pipe_out[1]);
    waitpid(pid, &status_pid, 0);
    while (!ft_is_operator(data->token[data->token_y][0]))
        data->token_y++;
    data->token_y++;
    data->count_pipe--;
    execute_cmd(data,fd_pipe_out[0]);
}

void pipe_start(t_data *data, int *fd_pipe)
{
        printf("ICI START\n");
    pid_t pid = fork();
    if (pid ==0)
    {
        close(fd_pipe[0]);
        dup2(fd_pipe[1], 1);
        if (command_exist(data) == 0 || command_exist(data) == 1)
            execute(data);
        exit(0);
    }
    close(fd_pipe[1]);
    wait(NULL);
    while (!ft_is_operator(data->token[data->token_y][0]))
        data->token_y++;
    data->token_y++;
    data->count_pipe--;
    execute_cmd(data,fd_pipe[0]);
}