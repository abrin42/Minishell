#include "minishell.h"

void    malloc_parsing(t_data *data)
{
    data->i_args = 1000;
    data->parsing = malloc (sizeof(char *) * data->i_args);
    while (data->i_args >= 0)
    {
        data->parsing[data->i_args] = malloc (sizeof(char) * 1000);
        data->i_args--;
    }
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

/*void    doublecot(t_data *data)
{
    int i;

    i = 0;
    data->line++;
    while(data->line[data->lenquote] && data->line[data->lenquote] != '"')
    {          
        data->lenquote++;
    }
    while (data->lenquote > i)
    {
        data->parsing[data->parsing_y][i] = data->line[i];
        i++;
    }
    data->line += data->lenquote + 1;
    printf("-parssingavant[1]%s-\n",data->parsing[1]);
}*/