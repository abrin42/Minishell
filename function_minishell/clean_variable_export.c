#include "../minishell.h"

void    clear_quote(t_data *data)
{
    int i;

    i = 0;
    data->simple_quote = 0;
    data->double_quote = 0;
    while (data->buffer[i])
    {
        if (data->buffer[i] == '\'')
            data->simple_quote ++;
        else if (data->buffer[i] == '\"')
            data->double_quote++;
        i++;
    }
}

char *clean_buffer(t_data *data)
{
    char    *new_line;

    new_line = gc_malloc(&data->gc, sizeof(char) * 10000);
    data->i_new_line = 0;
    data->i_buffer = 0;
    clear_quote(data);
    while (data->i_buffer < ft_strlen(data->buffer))
    {
        if (data->buffer[data->i_buffer] == '\'')
        {
            data->i_buffer++;
            while (data->buffer[data->i_buffer] != '\'')
            {
                new_line[data->i_new_line++] = data->buffer[data->i_buffer++];
            }
        }
        else if (data->buffer[data->i_buffer] == '"')
        {
            data->i_buffer++;
            while (data->buffer[data->i_buffer] != '"')
            {
                if (data->buffer[data->i_buffer] == '$')
                   clean_var(data, new_line);
                else
                    new_line[data->i_new_line++] = data->buffer[data->i_buffer++];
            }
        }
        else if (data->buffer[data->i_buffer] == '$')
            clean_var(data, new_line);
        else if (data->buffer[data->i_buffer] == '\\')
            new_line[data->i_new_line++] = ' ';
        else
            new_line[data->i_new_line++] = data->buffer[data->i_buffer];

        data->i_buffer++;
    }
    new_line[data->i_new_line] = '\0';
    free(data->buffer);
    return (new_line);
}

void    clean_token(t_data *data)
{
    int i;
    int y;

    i = 0;
    while (i <= 100)
    {
        y = 0;
        while (y <= 1000)
        {
            data->token[i][y] = '\0';
            y++;
        }
        i++;
    }
}

void fill_token(t_data *data)
{
    int i;

    i = 0;
    data->token_x = 0;
    data->token_y = 0;
    clean_token(data);
    while (data->buffer[i] != '\0')
    {
        while (!ft_is_operator(data->buffer[i]) && !ft_iswhitespace(data->buffer[i]) && data->buffer[i] != '\0')
        {
            data->token[data->token_y][data->token_x] = data->buffer[i];
            data->token_x++;
            i++;
        }
        data->token[data->token_y][data->token_x] = '\0';
        data->token_y++;
        data->token_x = 0;
        while (ft_iswhitespace(data->buffer[i]) && data->buffer[i] != '\0')
        {
            i++;
        }
        while (ft_is_operator(data->buffer[i]) && data->buffer[i] != '\0')
        {
            data->token[data->token_y][data->token_x] = data->buffer[i];
            data->token_x++;
            i++;
        }
    }
}

void count_pipe(t_data *data)
{
    int i;

    i = 0;
    data->count_pipe = 0;
    while (data->buffer[i])
    {
        if (data->buffer[i] == '|')
            data->count_pipe++;
        i++;
    }
    
}