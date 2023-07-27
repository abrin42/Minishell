#include "minishell.h"

void    print_error(t_data *data)
{
    int i;

    i = 0;
    data->trace = 0;
    printf("print error; parsing y[%d] =%s=\n",data->parsing_y,data->parsing[data->parsing_y]);
    while (data->line[i])
    {
        if (data->line[i] != '\0' && ft_strcmp2(data->line , "echo", i) == 0 &&
            ft_strcmp2(data->line , "cd", i) == 0 && ft_strcmp2(data->line , "pwd", i) == 0 &&
                ft_strcmp2(data->line , "env", i) == 0 &&   data->trace == 0)
        {
                while (data->line[i] && (data->line[i] != ' ' && ft_verif_symbols(data->line[i]) == 0 ))
                    ft_putchar(data->line[i++]);
                write(1, ": command not found\n", 20);
                data->trace++;
        }
        if (ft_verif_symbols(data->line[i]) == 1)
        {
            while (data->line[i] == ' ' || ft_verif_symbols(data->line[i]) == 1)
                i++;
            if (data->line[i] != '\0' && ft_strcmp2(data->line , "echo", i) == 0 &&
            ft_strcmp2(data->line , "cd", i) == 0 && ft_strcmp2(data->line , "pwd", i) == 0 &&
                ft_strcmp2(data->line , "env", i) == 0)
            {
                while (data->line[i] && (data->line[i] != ' ' && ft_verif_symbols(data->line[i]) == 0 ))
                    ft_putchar(data->line[i++]);
                write(1, ": command not found\n", 20);
            }
        }
        i++;
    }
}

int test_pipe(t_data *data)
{
    int i;
    int memo_parsing_y;

    memo_parsing_y = data->parsing_y;
    i = 0;
    if (data->parsing_y != 0)
        data->parsing_y--;
    while (data->parsing[data->parsing_y] != NULL)
    {
        if (data->parsing[data->parsing_y][0] == '|')
            i++;
        data->parsing_y++;
    }
    data->parsing_y = memo_parsing_y;
    //printf("parss y -*- = %d, nb pipe = %d \n",data->parsing_y,i );
    if (i >= 1 && data->parsing_y == 0)
        return(1);
    else if (i > 1)
        return(2);
    else if (i == 1)
        return (3);
    return(0);
}

int    *one_pipe_start_gestion(t_data * data)// pour la premiere commande
{
    
    //int tube[2];
    pipe(data->tube_1);
    int status_pid;
    
    //printf("begin of pipe\n");
    pid_t pid = fork();
    if (pid == 0)
    {
        //printf("tube[0] = %d tube[1] = %d\n", data->tube_1[0], data->tube_1[1]);
        close(data->tube_1[0]);
        dup2(data->tube_1[1], 1);//change sortie dup2(?,1) pipe 1
        execute(data);
        exit(0);    //exit et close entree du pipe 1
    }
    close(data->tube_1[1]);
    wait(NULL);
    //waitpid(pid, &status_pid, 0);
    return(0); // dans struct
}

void    two_pipe1_gestion(t_data * data)//commade au millieu 
{
    pipe (data->tube_1);
    pid_t pid = fork();
    int status_pid;

    if (pid == 0)
    {
        close(data->tube_2[1]);
        close(data->tube_1[0]);
        dup2(data->tube_2[0], STDIN_FILENO);//change sortie dup2(?,1) pipe 1
        dup2(data->tube_1[1], STDOUT_FILENO);
        execute(data);
        exit(0);
    }
    close(data->tube_2[0]);
    close(data->tube_1[1]);
    waitpid(pid, &status_pid, WEXITED);
    //exit et close sortie pipe 1 , ent    close(tube[1]);*/
}

void    two_pipe2_gestion(t_data * data)//commade au millieu 
{
    pipe (data->tube_2);
    int status_pid;
    pid_t pid = fork();

    if (pid == 0)
    {
        close(data->tube_1[1]);
        close(data->tube_2[0]);
        dup2(data->tube_1[0], STDIN_FILENO); //change sortie dup2(?,1) pipe 1
        dup2(data->tube_2[1], STDOUT_FILENO);
        execute(data);
        exit(0);
    }
    close(data->tube_1[0]);
    close(data->tube_2[1]);
    waitpid(pid, &status_pid, 0);
    //exit et close sortie pipe 1 , ent    close(tube[1]);*/
}

void    one_pipe_end1_gestion(t_data * data)// pour la derniere commande
{
    pid_t pid = fork();
    int status_pid;

    if (pid == 0)
    {
        //printf("--parsing y[%d] =%s=\n",data->parsing_y,data->parsing[data->parsing_y]);
        //dup2(,0)//change entre dup2(?,0) pipe 2
        /*data->tube_out[0] = data->tube_in[0];
        data->tube_out[1] = data->tube_in[1];*/
        //fonction execute
        close(data->tube_2[1]);
        dup2(data->tube_2[0], STDIN_FILENO);//change sortie dup2(?,1) pipe 1
        execute(data);
        exit(0);    //exit et close entree du pipe 1
    }
    close(data->tube_2[0]);
    waitpid(pid, &status_pid, 0);
    //exit et close sortie pipe 2
}

void    one_pipe_end2_gestion(t_data * data)// pour la derniere commande
{
    pid_t pid = fork();
    int status_pid;

    if (pid == 0)
    {
        //printf("end tube[0] = %d tube[1] = %d\n", data->tube_1[0], data->tube_1[1]);
        //printf("--parsing y[%d] =%s=\n",data->parsing_y,data->parsing[data->parsing_y]);
        //dup2(,0)//change entre dup2(?,0) pipe 2
        /*data->tube_out[0] = data->tube_in[0];
        data->tube_out[1] = data->tube_in[1];*/
        //fonction execute
        close(data->tube_1[1]);
        dup2(data->tube_1[0], STDIN_FILENO);//change sortie dup2(?,1) pipe 1
        execute(data);
        exit(0);    //exit et close entree du pipe 1
    }
    close(data->tube_1[0]);
    waitpid(pid, &status_pid, 0);
    //exit et close sortie pipe 2
}

void    redirection_in_file(t_data *data)
{
    char    mes[500];
    int        rd_bytes;
    pid_t   pid;
    int     status_pid;
    int        fd;


    if (ft_strcmp(data->parsing[data->parsing_y + 2] , ">") == 0)
        fd = open(data->parsing[data->parsing_y + 3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (ft_strcmp(data->parsing[data->parsing_y + 2] , ">>") == 0)
        fd = open(data->parsing[data->parsing_y + 3], O_WRONLY | O_CREAT | O_APPEND, 0644);
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

void    execute_in_file(t_data *data)
{
    pid_t   pid;
    int     status_pid;
    int i = 1;

    pipe(data->tube_redirect);
    pid = fork();
    if (pid == 0)
    {
        close(data->tube_redirect[0]);
        dup2(data->tube_redirect[1], 1);
        if (ft_strcmp(data->parsing[data->parsing_y] , "echo") == 0)
            ft_echo(data, 5);
        if (ft_strcmp(data->parsing[data->parsing_y] , "cd") == 0)
            ft_cd(data);
        else if (ft_strcmp(data->parsing[data->parsing_y] , "pwd") == 0)
            ft_pwd(data);
        else if (ft_strcmp(data->parsing[data->parsing_y] , "env") == 0)
            ft_env(data);
        else if (ft_strcmp(data->parsing[data->parsing_y] , "export") == 0)
            ft_export(data);
        else if (ft_strcmp(data->parsing[data->parsing_y] , "unset") == 0)
            ft_unset(data);
        else if (ft_strcmp(data->parsing[data->parsing_y] , "exit") == 0)
            ft_exit(data);
        else if(command_terminal(data) == 1)
            i = i;
        close(data->tube_redirect[1]);
        exit (0);
    }
    close(data->tube_redirect[1]);
    waitpid(pid, &status_pid, 0);
    redirection_in_file(data);
    close(data->tube_redirect[0]);
    //exit (0);
}

void    search_in_file(t_data *data)
{
    printf("ICICI2\n");
    int     fd;
    char    *buf;
    char    *save;
    pid_t   pid;
    int     status_pid;
    int     condition;

    pipe(data->tube_redirect);
	save = malloc(sizeof(char) * 1);
	save[0] = '\0';
    condition = 1;
    buf = malloc(sizeof(char) * (50 + 1));
    fd =  open(data->parsing[data->parsing_y + 3], O_RDONLY);
    pid = fork ();
    if (pid == 0)
    {
        close(data->tube_redirect[0]);
        while(condition != 0)
        {
            condition = read(fd, buf, 50);
            buf[condition] = '\0';
            save = ft_strjoin2(save, buf);
        }
        free (buf);
        close(fd);
printf("%s\n", save);
printf("save length : %d\n", ft_strlen(save));
        dup2(data->tube_redirect[1], 1);
        write(1, save, ft_strlen(save));
        execute(data);
        close(data->tube_redirect[1]);
        exit (0);
    }
    close(data->tube_redirect[1]);
    waitpid(pid, &status_pid, 0);
    close(data->tube_redirect[0]);
    close(fd);
    free (buf);
}

int    ft_start(t_data *data)
{
    //write(1,"*-*\n",4);
    int nb_pipe;

    data->tube_trace++;
  //  data->pipe_in = data->pipe_out;
    nb_pipe = 0;
    nb_pipe = test_pipe(data);
    //printf("test pipe = %d\n",nb_pipe);
    if (nb_pipe == 1 )/*&& data->trace du passage de la premiere comande == 0*/ //ca tcheck si 1 pipe au debut ou data parssing = 0
    {
        //printf("-------------------pipe start\n");
        one_pipe_start_gestion(data);
    }
    else if (nb_pipe == 2 && data->tube_trace % 2 != 0) //normalement ca tcheck si entre de tcheck ? 
    {
        //printf("-------------------pipe mide impaire 1\n");
        two_pipe1_gestion(data);
    }
    else if (nb_pipe == 2 && data->tube_trace % 2 == 0) //normalement ca tcheck si entre de tcheck ? 
    {
        //printf("-------------------pipe mide paire 2\n");
        two_pipe2_gestion(data);
    }
    else if (nb_pipe == 3 && data->tube_trace % 2 != 0) /*&& data->trace du passage de la premiere comande == 1*/ //ca tcheck si 1 pipe a la fin
    {
        //printf("-------------------pipe end impaire 1\n");
        one_pipe_end1_gestion(data);
    }
    else if (nb_pipe == 3 && data->tube_trace % 2 == 0) 
    {
        //printf("-------------------pipe end paire 2\n");
        one_pipe_end2_gestion(data);
    }
    else if (ft_strcmp(data->parsing[data->parsing_y + 2] , ">") == 0 || ft_strcmp(data->parsing[data->parsing_y + 2] , ">>") == 0)
    {
        execute_in_file(data);
        if (data->parsing[data->parsing_y + 6] != NULL)
            data->parsing_y += 3;
        else
            return (0);
    }
    else if (ft_strcmp(data->parsing[data->parsing_y + 2] , "<") == 0 || ft_strcmp(data->parsing[data->parsing_y + 2] , "<<") == 0)
    {
        printf("ICICI\n");
        search_in_file(data);
    }
    else if (nb_pipe == 0)
    {
        //printf("-------------------pipe non\n");
        execute(data);//no pipe just executer le code
    }
    data->parsing_y += 3;
    return(0);
}

int nb_cmd(t_data *data)
{
    int i;
    int cmd;

    cmd = 0;
    i = 0;
    while (data->parsing[i] != NULL)
    {
        if (ft_verif_symbols(data->parsing[i][0]) == 1)
            cmd++; 
        i++;
    }
    cmd++;
    //printf("cmd = %d\n", cmd);
    return (cmd);
}

int    ft_command(t_data *data)
{
    int verif;
    int nb_command;
    int i;

    i = 0;
    nb_command = 0;
    data->tube_trace = 0;
    init_data_parsing(data);
    malloc_parsing(data);
    ft_parsing_space(data);
    ft_parsing_firstword(data);
    verif = ft_parsing_following(data); // il faut vreaiment le faire la ?? 
    if (verif == -1)
        return (-1);
    for (int y = 0; data->parsing[y] != NULL; y++)
        printf("===%s===\n", data->parsing[y]);
    //return (NULL);
    nb_command = nb_cmd(data);
    data->parsing_y = 0;

    while (i < nb_command) // temps qu'il y a des commade;
    {
    
        /*if (data->parsing[data->parsing_y] == NULL)
        {
            if (test_comande_possible(data) == 0)// attention a tcheck maybe ne pas faire le if ? 
            {
                write(1,"*-*\n",4);
                printf("error %d", data->parsing_y);
                print_error(data);
            }
        }
        else
        {*/
        //printf("parsing y[%d] =%s=\n",data->parsing_y,data->parsing[data->parsing_y]);
        if (test_comande_possible(data) == 0)// attention a tcheck
        {
            write(1,"/-/\n",4);
            print_error(data);//coamde suivante ? a test avec le bash 
            //printf("error %d", data->parsing_y);
        }
        else
        {
            //write(1,"*-*\n",4);
            //printf("test alpha\n");
            ft_start(data);//  check si redirection / | (ft_start) ou just commade 
        }
        //}
        //data->parsing_y += 2;
        i++;
    }
    return (0);
}