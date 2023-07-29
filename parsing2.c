#include "minishell.h"

void    malloc_parsing(t_data *data)
{
    int i;

    data->i_args = 1000;
    data->parsing = malloc (sizeof(char *) * data->i_args);
    while (data->i_args >= 0)
    {
        i = 1000;
        data->parsing[data->i_args] = malloc (sizeof(char) * 1000);
        /*while (i >= 0)
        {
            data->parsing[data->i_args][i] = NULL;
            i--;
        }*/
        data->i_args--;
    }
    /*data->i_args = 1000;
    while (data->i_args >= 0)
    {
        data->parsing[data->i_args] = NULL;
        data->i_args--;
    }*/
}

void    free_parsing(t_data *data)
{
    data->i_args = 1000;
    while (data->i_args >= 0)
    {
        free(data->parsing[data->i_args]);
        data->i_args--;
    }
    data->parsing = malloc (sizeof(char *) * data->i_args);
}

void    init_data_parsing(t_data *data)
{
    data->i_line = 0;
    data->parsing_y = 0;
}

int    ft_verif_symbols(char c)
{
    if (c == '<' || c == '>' || c == '|')
        return (1);
    else
        return (0);
}