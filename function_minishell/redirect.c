#include "../minishell.h"

void init_args_redirect(t_data *data, int x)
{
    int y;
    int i_args;

    i_args = 1;
    y = x + 1;
    data->args[0] = data->path;
    while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
    {
        data->args[i_args] = data->token[y];
        i_args++;
        y++;
    }
}


void    execute_redirect(t_data *data, int y)
{
    if (ft_strcmp(data->token[y] , "echo") == 0)
        ft_echo(data);
    if (ft_strcmp(data->token[y] , "cd") == 0)
        ft_cd(data);
    else if (ft_strcmp(data->token[y] , "pwd") == 0)
        ft_pwd(data);
    else if (ft_strcmp(data->token[y] , "env") == 0)
        ft_env(data);
    else if (ft_strcmp(data->token[y] , "export") == 0)
        ft_export(data);
    else if (ft_strcmp(data->token[y] , "unset") == 0)
        ft_unset(data);
    else if (ft_strcmp(data->token[y] , "exit") == 0)
        ft_exit(data);
    else
        execute_command_redirect(data, y);
}

int command_exist_redirect(t_data *data, int y)
{
    if (ft_strcmp(data->token[y] , "echo") == 0)
        return (0);
    else if (ft_strcmp(data->token[y] , "cd") == 0)
        return (0);
    else if (ft_strcmp(data->token[y] , "pwd") == 0)
        return (0);
    else if (ft_strcmp(data->token[y] , "env") == 0)
        return (0);
    else if (ft_strcmp(data->token[y] , "export") == 0)
        return (0);
    else if (ft_strcmp(data->token[y] , "unset") == 0)
        return (0);
    else if (ft_strcmp(data->token[y] , "exit") == 0)
        return (0);
    else
    {
        data->count_path = count_path(getenv("PATH"));
        while (data->count_path > 0)
        {
            data->path = ft_strjoin(data->path_bdd[data->count_path - 1], data->token[y], data);
            if (access(data->path, X_OK) == 0)
                return(1);
            data->count_path--;
        }
    }
    return (-1);
}

void    redirection_in_file(t_data *data, int y)
{
    char    mes[500];
    int        rd_bytes;
    pid_t   pid;
    int     status_pid;
    int        fd;

    if (ft_strcmp(data->token[y] , ">") == 0)
        fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (ft_strcmp(data->token[y] , ">>") == 0)
        fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    rd_bytes = read(data->tube_redirect[0], mes, 499); // on read dans le pipe
    mes[rd_bytes] = '\0'; // char nul de fin de string
    pid = fork();
    if (pid == 0)
    {
        dup2(fd, 1); // 1 --=--> fd
        printf("%s", mes); // ecrit dans 1 (donc dans fd)
        close(fd);
        exit (0);
    }
    waitpid(pid, &status_pid, 0);
    close(fd);
}

void    execute_command_redirect(t_data *data, int y)
{
    pid_t pid;
    pid = fork();
    if (pid == 0)
    {
        malloc_args(data);
        init_args_redirect(data, y);
        execve(data->path, data->args, data->env);
        exit(0);
    }
    waitpid(pid, NULL, 0);
}

void    execute_in_file_first_pipe(t_data *data, int y, int *fd_pipe)
{
    pid_t pid;
    int     fd;
    char    *str;
    int     buf_str;

     while (data->token[y][0] != '>')
        y++;
    if (ft_strcmp(data->token[y] , ">") == 0)
        fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (ft_strcmp(data->token[y] , ">>") == 0)
        fd = open(data->token[y + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    str = malloc(sizeof(char) * 1000); //REFAIRE MALLOC
    buf_str = read(fd_pipe[0], str, 999);
    str[buf_str] = '\0';
    pid = fork();
    if (pid == 0)
    {
        dup2(fd ,1);
        printf("%s", str);
        close (fd);
        exit (0);
    }
    close (fd);
}

void    execute_in_file_pipe(t_data *data, int y, int *fd_pipe)
{
    pid_t   pid;
    int        fd;
    int     x;


    char    *str;
    int     buf_str;
    str = malloc(sizeof(char) * 1000);


    if (command_exist_redirect(data, y) == -1)
        return ;
    pid = fork();
    x = y;
    while (data->token[x][0] != '>')
        x++;
    if (ft_strcmp(data->token[x] , ">") == 0)
        fd = open(data->token[x + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (ft_strcmp(data->token[x] , ">>") == 0)
        fd = open(data->token[x + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (pid == 0)
    {
        close(fd_pipe[1]);
        dup2(fd_pipe[0], 0);
        dup2(fd, 1);
        execute_redirect(data, y);
        close(fd);
        buf_str = read(fd_pipe[0], str, 999);
        str[buf_str] = '\0';
        close(fd_pipe[0]);
        exit (0);
    }
    waitpid(pid, NULL, 0);
    close(fd);
    close(fd_pipe[1]);
    while (data->token[data->token_y][0] != '|' && data->token[data->token_y][0] != '\0')
    {
        data->add++;
        data->token_y++;
    }
    data->token_y++;
    data->add++;
    data->count_pipe--;
    if (data->token[data->token_y][0] != '\0')
        execute_cmd(data, fd_pipe[0]);
}

void    execute_search(t_data *data)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        close(data->tube_search[1]);
        dup2(data->tube_search[0], 0);
        execute(data);
        close(data->tube_search[0]);
        exit (0);
    }
    close(data->tube_search[1]);
    waitpid(pid, NULL, 0);
    close(data->tube_search[0]);
}

/*void    search_in_file_pipe(t_data *data, int *fd_pipe)  nonnnn moi
{
    pid_t pid;
    int fd;
    int condition;
    char    *buf;
    char    *save;

    condition = 1;
    save = gc_malloc(&data->gc, sizeof(char) * 1);
	save[0] = '\0';
    buf = gc_malloc(&data->gc, sizeof(char) * (50 + 1));
    y = y - data->add;
    while (data->token[y][0] != '<')
        y++;
    y++;
    fd =  open(data->token[y], O_RDONLY);
    if (fd == -1)
    {
        error_open_search(data, fd);
        return(-1);
    }
    pipe(data->tube_search);
    pid = fork();
    if (pid == 0)
    {
        close(data->tube_search[0]);
        while(condition != 0)
        {
            condition = read(fd, buf, 50);
            buf[condition] = '\0';
            save = ft_strjoin2(save, buf, data);
        }
        close(fd);
        dup2(data->tube_search[1], 1);
        printf("%s", save);
        close(data->tube_search[1]);
        exit(0);
    }
    close(data->tube_search[1]);
    waitpid(pid, NULL, 0);
    return(0);
}*/

int    search_in_file(t_data *data, int y)
{
    pid_t pid;
    int fd;
    int condition;
    char    *buf;
    char    *save;

    condition = 1;
    save = gc_malloc(&data->gc, sizeof(char) * 1);
	save[0] = '\0';
    buf = gc_malloc(&data->gc, sizeof(char) * (50 + 1));
    y = y - data->add;
    while (data->token[y][0] != '<')
        y++;
    y++;
    fd =  open(data->token[y], O_RDONLY);
    if (fd == -1)
    {
        error_open_search(data, fd);
        return(-1);
    }
    pipe(data->tube_search);
    pid = fork();
    if (pid == 0)
    {
        close(data->tube_search[0]);
        while(condition != 0)
        {
            condition = read(fd, buf, 50);
            buf[condition] = '\0';
            save = ft_strjoin2(save, buf, data);
        }
        close(fd);
        dup2(data->tube_search[1], 1);
        printf("%s", save);
        close(data->tube_search[1]);
        exit(0);
    }
    close(data->tube_search[1]);
    waitpid(pid, NULL, 0);
    return(0);
}






void    execute_search_pipe_start(t_data *data, int *fd_pipe)
{
    pid_t pid;

    printf("search pipe start\n");
    pid = fork();
    if (pid == 0)
    {
        close(fd_pipe[0]);
        close(data->tube_search[1]);
        dup2(data->tube_search[0], 0);
        dup2(fd_pipe[1], 1);
        execute(data);
        close(data->tube_search[0]);
        close(fd_pipe[1]);
        exit (0);
    }
    close(fd_pipe[1]);
    close(data->tube_search[1]);
    waitpid(pid, NULL, 0);
    close(data->tube_search[0]);
    while (data->token[data->token_y][0] != '|' && data->token[data->token_y][0] != '\0')
    {
        data->add++;
        data->token_y++;
    }
    data->token_y++;
    data->add++;
    data->count_pipe--;
    if (data->token[data->token_y][0] != '\0')
        execute_cmd(data,fd_pipe[0]);
}

void    execute_search_pipe_middle(t_data *data, int *fd_pipe_in, int *fd_pipe_out)
{
    pid_t pid;

    printf("search pipe mide\n");
    pid = fork();
    if (pid == 0)
    {
        close(fd_pipe_in[1]);
        close(fd_pipe_out[0]);
        close(data->tube_search[1]);
        dup2(fd_pipe_in[0], 0);
        dup2(fd_pipe_out[1], 1);
        dup2(data->tube_search[0], 0);
        execute(data);
        close(data->tube_search[0]);
        close(fd_pipe_in[0]); // maybe enlver
        close(fd_pipe_out[1]);
        exit (0);
    }
    close(fd_pipe_in[0]);
    close(fd_pipe_out[1]);
    close(data->tube_search[1]);
    waitpid(pid, NULL, 0);
    close(data->tube_search[0]);
    while (data->token[data->token_y][0] != '|' && data->token[data->token_y][0] != '\0')
    {
        data->add++;
        data->token_y++;
    }
    data->token_y++;
    data->add++;
    data->count_pipe--;
    if (data->token[data->token_y][0] != '\0')
        execute_cmd(data,fd_pipe_out[0]);
}

void    execute_search_pipe_end(t_data *data, int *fd_pipe)
{
    pid_t pid;

    printf("search pipe end\n");
    pid = fork();
    if (pid == 0)
    {
        close(fd_pipe[1]);
        close(data->tube_search[1]);
        dup2(data->tube_search[0], 0);
        dup2(fd_pipe[0], 0);
        execute(data);
        close(data->tube_search[0]);
        close(fd_pipe[0]);
        exit (0);
    }
    close(fd_pipe[0]);
    close(data->tube_search[1]);
    waitpid(pid, NULL, 0);
    close(data->tube_search[0]);
    close(fd_pipe[1]);
    /*while (data->token[data->token_y][0] != '|' && data->token[data->token_y][0] != '\0')
    {
        data->add++;
        data->token_y++;
    }
    data->token_y++;
    data->add++;
    data->count_pipe--;
    if (data->token[data->token_y][0] != '\0')
        execute_cmd(data,fd_pipe[0]);*/
}







void    execute_in_file(t_data *data, int y)
{
    pid_t   pid;

    if (command_exist_redirect(data, y) == -1)
        return ;
    pipe(data->tube_redirect);
    pid = fork();
    if (pid == 0)
    {
        close(data->tube_redirect[0]);
        dup2(data->tube_redirect[1], 1);
        execute_redirect(data, y);
        exit (0);
    }
    close(data->tube_redirect[1]);
    waitpid(pid, NULL, 0);
    while (data->token[y][0] != '>')
        y++;
    redirection_in_file(data, y);
    close(data->tube_redirect[0]);
}

int check_redirect_pipe(t_data *data)
{
    int y;

    y = data->token_y;
    while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
        y++;
    if (data->token[y][0] == '>')
    {
        return (0);
    }
    return (1);
}

int check_redirect(t_data *data)
{
    int y;

    y = data->token_y;
    if (data->token[y][0] == '>')
        return (0);
    while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
        y++;
    if (data->token[y][0] == '>')
        return (0);
    return (1);
}

int check_redirect_inverse(t_data *data)
{
    int y;

    y = data->token_y;
    while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
        y++;
    if (data->token[y][0] == '<')
        return (0);
    return (1);
}
