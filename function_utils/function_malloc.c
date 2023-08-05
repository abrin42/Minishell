#include "../minishell.h"

int count_path(char *path_temp)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (path_temp[i] != '\0')
    {
        if (path_temp[i] == ':')
            count++;
        i++;
    }
    count++;
    return (count);
}

void    malloc_path_bdd(t_data *data)
{
    int i;
    int x;
    int y;
    int count;
    char    *path_temp;

    i = 0;
    x = 0;
    y = 0;
    path_temp = getenv("PATH");
    data->count_path = count_path(path_temp);
    data->path_bdd = gc_malloc(&data->gc, sizeof(char *) * data->count_path);
    while (data->count_path > 0)
    {
        x = 0;
        while (path_temp[i] != ':' && path_temp[i] != '\0')
        {
            x++;
            i++;
        }
        data->path_bdd[y] = gc_malloc(&data->gc, sizeof(char) * (x + 2));
        y++;
        i++;
        data->count_path--;
    }
    data->count_path = count_path(path_temp);
    y = 0;
    i = 0;
    while (data->count_path > 0)
    {
        x = 0;
        while (path_temp[i] != ':' && path_temp[i] != '\0')
        {
            data->path_bdd[y][x] = path_temp[i];
            x++;
            i++;
        }
        data->path_bdd[y][x] = '/';
        data->path_bdd[y][x + 1] = '\0';
        y++;
        i++;
        data->count_path--;
    }
    //************PRINT TOUT LES PATH*************//
    /*data->count_path = count_path(path_temp);
    y = 0;
    while (data->count_path > 0)
    {
        printf("ICI BDD :%s:\n", data->path_bdd[y]);
        data->count_path--;
        y++;
    }*/
}

void malloc_data(t_data *data)
{
    int i;

    gc_init(&data->gc);

    data->token = gc_malloc(&data->gc, sizeof(char *) * 100);
    i = 0;
    while (i <= 100)
    {
        data->token[i] = gc_malloc(&data->gc, sizeof(char) * 1000);
        data->token[i][0] = '\0';
        i++;
    }
}

void malloc_args(t_data *data)
{
    int y;

    y = 0;
    while (data->token[y][0] != '\0')
        y++;
    data->args = gc_malloc(&data->gc, sizeof(char *) * (y + 2));
    y = 0;
}

void init_args(t_data *data)
{
    int y;
    int i_args;

    i_args = 1;
    y = data->token_y + 1;
    data->args[0] = data->path;
    while (data->token[y][0] != '\0' && !ft_is_operator(data->token[y][0]))
    {
        data->args[i_args] = data->token[y];
        i_args++;
        y++;
    }
}
