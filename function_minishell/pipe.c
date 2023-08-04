#include "../minishell.h"

/*
for (size_t p = 0; p < 10; p++)
{
    printf("ICI ARGS ===%s===\n", data->args[p]);
    p++;
}*/

void pipe_end(t_data *data, int *fd_pipe)
{
    printf("pipe end\n");
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
    int status_pid;
    printf("pipe mid\n");
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
    data->add = 0;
    while (data->token[data->token_y][0] != '|')
    {
        data->add++;
        data->token_y++;
    }
    data->token_y++;
    data->add++;
    data->count_pipe--;
    execute_cmd(data,fd_pipe_out[0]);
}

void pipe_start(t_data *data, int *fd_pipe)
{
    pid_t pid;
    int    y;

    printf("pipe start\n");
    y = -1;
    if (check_redirect_pipe(data) == 0)
            y = data->token_y;
    pid = fork();
    if (pid ==0)
    {
        close(fd_pipe[0]);
        dup2(fd_pipe[1], 1);
        if (command_exist(data) == 0 || command_exist(data) == 1)
            execute(data);
        exit(0);
    }
    close(fd_pipe[1]);
    waitpid(pid, NULL, 0);
    data->add = 0;
    while (data->token[data->token_y][0] != '|')
    {
        data->add++;
        data->token_y++;
    }
    data->token_y++;
    data->add++;
    data->count_pipe--;
    if (y != -1)
        execute_in_file_first_pipe(data, y, fd_pipe);
    execute_cmd(data,fd_pipe[0]);
}
