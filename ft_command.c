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
    pipe (data->tube_1);

    pid_t pid = fork();
    if (pid == 0)
    {
        close(data->tube_1[0]);
        dup2(data->tube_1[1], STDOUT_FILENO);//change sortie dup2(?,1) pipe 1
        execute(data);
        exit(0);    //exit et close entree du pipe 1
    }
    close(data->tube_1[1]);
    wait(NULL);
    return(0); // dans struct
}

void    two_pipe1_gestion(t_data * data)//commade au millieu 
{
    pipe (data->tube_1);
    pid_t pid = fork();

    if (pid == 0)
    {
        close(data->tube_2[1]);
        close(data->tube_1[0]);
        dup2(data->tube_2[0], STDIN_FILENO);//change sortie dup2(?,1) pipe 1
        dup2(data->tube_1[1], STDOUT_FILENO);
        execute(data);
    }
    close(data->tube_2[0]);
    close(data->tube_1[1]);
    wait(NULL);
    //exit et close sortie pipe 1 , ent    close(tube[1]);*/
}

void    two_pipe2_gestion(t_data * data)//commade au millieu 
{
    pipe (data->tube_2);
    pid_t pid = fork();

    if (pid == 0)
    {
        close(data->tube_1[1]);
        close(data->tube_2[0]);
        dup2(data->tube_1[0], STDIN_FILENO);//change sortie dup2(?,1) pipe 1
        dup2(data->tube_2[1], STDOUT_FILENO);
        execute(data);
    }
    close(data->tube_1[0]);
    close(data->tube_2[1]);
    wait(NULL);
    //exit et close sortie pipe 1 , ent    close(tube[1]);*/
}

void    one_pipe_end1_gestion(t_data * data)// pour la derniere commande
{
    pid_t pid = fork();

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
        //exit(0);    //exit et close entree du pipe 1
    }
    close(data->tube_2[0]);
    wait(NULL);
    //exit et close sortie pipe 2
}

void    one_pipe_end2_gestion(t_data * data)// pour la derniere commande
{
    pid_t pid = fork();

    if (pid == 0)
    {
        //printf("--parsing y[%d] =%s=\n",data->parsing_y,data->parsing[data->parsing_y]);
        //dup2(,0)//change entre dup2(?,0) pipe 2
        /*data->tube_out[0] = data->tube_in[0];
        data->tube_out[1] = data->tube_in[1];*/
        //fonction execute
        close(data->tube_1[1]);
        dup2(data->tube_1[0], STDIN_FILENO);//change sortie dup2(?,1) pipe 1
        execute(data);
        //exit(0);    //exit et close entree du pipe 1
    }
    close(data->tube_1[0]);
    wait(NULL);
    //exit et close sortie pipe 2
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
        printf("-------------------pipe start\n");
        one_pipe_start_gestion(data);
    }
    else if (nb_pipe == 2 && data->tube_trace % 2 != 0) //normalement ca tcheck si entre de tcheck ? 
    {
        printf("-------------------pipe mide impaire 1\n");
        two_pipe1_gestion(data);
    }
    else if (nb_pipe == 2 && data->tube_trace % 2 == 0) //normalement ca tcheck si entre de tcheck ? 
    {
        printf("-------------------pipe mide paire 2\n");
        two_pipe2_gestion(data);
    }
    else if (nb_pipe == 3 && data->tube_trace % 2 != 0) /*&& data->trace du passage de la premiere comande == 1*/ //ca tcheck si 1 pipe a la fin
    {
        printf("-------------------pipe end impaire 1\n");
        one_pipe_end1_gestion(data);
    }
    else if (nb_pipe == 3 && data->tube_trace % 2 == 0) 
    {
        printf("-------------------pipe end paire 2\n");
        one_pipe_end2_gestion(data);
    }
    else if (nb_pipe == 0)
    {
        printf("-------------------pipe non\n");
        execute(data);//no pipe just executer le code
    }
    data->parsing_y += 3;
    return(0);
}

int    ft_command(t_data *data)
{
    int verif;
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
    int i = 0;

    data->parsing_y = 0;
    while (i < 2 ) // temps qu'il y a des commade;
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
            ft_start(data);//  check si redirection / | (ft_start) ou just commade 
        }
        //}
        //data->parsing_y += 2;
        i++;
    }
    return (0);
}