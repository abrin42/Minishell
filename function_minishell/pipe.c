#include "../minishell.h"

int is_separateur(t_data * data)
{
    if (data->parsing[data->parsing_y + 3][0] == '|')
        return (1);
    if (data->parsing[data->parsing_y + 3][0] == '>')
    {
        if (data->parsing[data->parsing_y + 3][1] == '>')
            return (3);
        return (2);
    }
    if (data->parsing[data->parsing_y + 3][0] == '<')
    {
        if (data->parsing[data->parsing_y + 3][1] == '<')
            return (5);
        return (4);
    }
    return (0);
}
void pipe_start(t_data *data, int fd_pipe)
{
    int status_pid;
    pid_t pid = fork();
    if (pid ==0)
    {
        close(fd_pipe[0]);
        dup2(fd_pipe[1], 1);
        execute(data); //fonction a faire
        exit(0);
    }
    close(fd_pipe[1]);
    wait(NULL);
    execute_cmd(data,fd_pipe[0]);
}

void pipe_mide(t_data *data, int fd_pipe)
{
    execute_cmd(data,fd_pipe);
}

void pipe_end(t_data *data, int fd_pipe)
{

}

void execute_cmd(t_data *data, int fd_pipe) // calculer le nombre de pipe pour savoir quand on est sur le dernier pipe (nb_pipe)
{
    int pipe[2];
    pipe(pipe);

    if (data->parsing_y == 0 && is_separateur(data) == 1) // permiere comade piper
        pipe_start(data, pipe[1])
        // close pipe et execute et donner le fd a la recusive
    else if (is_separateur(data) == 1 && nb_pipe == 1) // derniere commade piper 
        
        // utilise le fd_pipe pour sont entre puis execute
    else if (is_separateur(data) == 1 && nb_pipe > 1) // pipe avec entree et sortie 
        
        // utilise le fd_pipe pour sont entre puis execute
        // close pipe et execute et donner le fd a la recusive


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