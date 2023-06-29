#include "minishell.h"

void    print_error(t_data *data)
{
    int i;

    i = 0;
    data->trace = 0;
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
    while (data->parsing_y != NULL)
    {
        if (data->parsing[data->parsing_y] == '|')
            i++;
        data->parsing_y++;
    }
    data->parsing_y = memo_parsing_y;
    if (i == 1)
        return(1);
    if (i > 1)
        return(2);
    return(0);
}

void    one_pipe_start_gestion(t_data * data)// pour la premiere commande
{
    
    int tube[2];
    pipe (tube);
    pid_t pid = fork();
    
    if (pid == 0)
    {
        dup2(,1)//change sortie dup2(?,1) pipe 1
        //fonction execute
    }
    //exit et close entree du pipe 1
}

void    two_pipe_gestion(t_data * data)//commade au millieu 
{
    
    int tube[2];
    pipe (tube);
    pid_t pid = fork();
    
    if (pid == 0)
    {
        dup2(,)//change entre dup2(?,?) pipe 1
        dup2(,)//change sortie dup2(?,?) pipe 2
        //fonction execute
    }
    //exit et close sortie pipe 1 , entre pipe 2

}

void    one_pipe_end_gestion(t_data * data)// pour la derniere commande
{
    
    int tube[2];
    pipe (tube);
    pid_t pid = fork();
    
    if (pid == 0)
    {
        dup2(,0)//change entre dup2(?,0) pipe 2
        //fonction execute
    }
    //exit et close sortie pipe 2
}

int    ft_start(t_data *data)
{
    if (test_pipe(data) == 1 && data->/*trace du passage de la premiere comande == 0*/); //ca tcheck si 1 pipe au debut
        one_pipe_start_gestion(data);
    else if (test_pipe(data) == 1 && data->/*trace du passage de la premiere comande == 1*/); //ca tcheck si 1 pipe a la fin
        one_pipe_end_gestion(data);
    else if (test_pipe(data) == 2); //normalement ca tcheck si entre de tcheck ? tcheck si c'est bon
        two_pipe_gestion(data);
    else
        //no pipe just executer le code 
}

char    *ft_command(t_data *data)
{
    int verif;

    init_data_parsing(data);
    malloc_parsing(data);
    ft_parsing_space(data);
    ft_parsing_firstword(data);
    while () // temps qu'il y a des commade;
    {
    
        if (data->parsing[data->parsing_y] == NULL)
        {
            if (test_comande_possible(data) == 0)// attention a tcheck maybe ne pas faire le if ? 
                print_error(data);
        }
        else
        {
            verif = ft_parsing_following(data); // il faut vreaiment le faire la ?? 
            if (verif == -1)
                return (NULL);
            if (test_comande_possible(data) == 0)// attention a tcheck
                print_error(data);//coamde suivante ? a test avec le bash 
            else 
            //  check si redirection / | (ft_start) ou just commade 
        }
    }
    
    for (int y = 0; y < 5; y++)
    	printf("===%s===\n", data->parsing[y]);
    return (NULL);
}