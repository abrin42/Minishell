#include "minishell.h"

char    **malloc_args(t_data *data, char **args, char *path)
{
    int i;
    int y;
    int len;
    int start;
    int memolen;

    start = 0;
    y = 0;
    i = 0;
    len = 0;
    while(data->parsing[data->parsing_y + 1][i])
    {
        if (data->parsing[data->parsing_y + 1][i] == ' ')
            len++;
        i++;
    }
    len++;
    memolen = len;
    printf("len agrs = %d",len);
    i = 0;
    if (memolen != 1)
        args = malloc(sizeof (char*) * len);
    else 
        args = malloc(sizeof (char*) * 2);
    args[y] = ft_strdup(path);
    if (memolen == 1)
    {
        args[1] = NULL;
        return (args);
    }
    y++;
    while(y < memolen)
    {
        len = 0;
        while (data->parsing[data->parsing_y + 1][i] == ' ')
        {
            len++;
        }
        args[y] =ft_strdup_size(data->parsing[data->parsing_y + 1], len, start);
        start = len;
        y++;
        
    }
    printf("----args[%d] = %s\n", y, args[y]);
    //data->parsing[data->parsing_y];
    int v = 0;
    while (args[v])
    {
        printf("args[%d] =%s\n",v , args[v]);
        v++;
    }
    printf("--------\n");
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