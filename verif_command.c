#include "minishell.h"

char    **malloc_args(t_data *data, char **args) // a sup 
{
    data->i_args = 13;
    args = malloc(sizeof(char *) * data->i_args);
    while (data->i_args > -1)
    {        
            args[data->i_args] = malloc(sizeof(char) * 100);
            args[data->i_args] = data->parsing[data->i_args];
            printf("----\nparsing y %d\n",data->parsing_y);
            printf("parsing[%d] %s\n", data->i_args,data->parsing[ data->i_args]);
            printf("args[%d]-%s\n-----\n",data->i_args,args[data->i_args]);
        

        data->i_args--;
    }
    return (args);
}

void    free_args(char **args, t_data *data) // je crois pas use
{
        while (data->i_args < 11)
        {
            printf("\n\n\n\n*/*/*/*/*/*/*\n\n\n");
            free(args[data->i_args]);
            data->i_args++;
        }
        free(args);
        return ;            
}

void    ft_split_path(t_data *data)
{
    char    *path_temp;
    int     i;
    int     j;
    int     k;

    path_temp = malloc(sizeof(char) * 10000);
    path_temp = getenv("PATH");
    //printf("\npath_temp === %s\n", path_temp);
    i = 0;
    j = 0;
    k = 0;
    while (path_temp[i])
    {
        if (path_temp[i] == ':')
        {
            data->bdd[j][k] = '/';
            data->bdd[j][k + 1] = '\0';
            //printf("bdd[%d]%s\n",j , data->bdd[j]);
            j++;
            k = 0;
        }
        else
        {
            data->bdd[j][k] = path_temp[i];
            k++;
        }
        i++;
    }
    data->bdd[j] = NULL;
    //free (path_temp);   A CHECK FAISAIT SEG FAULT
}

void    malloc_bdd(t_data *data)
{
    data->i_args = 16; // 15 segfault mais bon parssing 16 mauvais parsing mais bon ex de ls | wc
    data->bdd = malloc(sizeof(char *) * data->i_args);
    while (data->i_args > -1)
    {
        data->bdd[data->i_args] = malloc(sizeof(char) * 10000);
        data->i_args--;
    }
    ft_split_path(data); 
}