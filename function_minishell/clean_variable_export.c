#include "../minishell.h"

void    clear_quote(t_data *data, char c)
{
    if (c == '\'')
        data->simple_quote ++;
    else if (c == '\"')
        data->double_quote++;
}

char *clean_buffer(t_data *data)
{
    char    *new_line;

    new_line = gc_malloc(&data->gc, sizeof(char) * 10000);
    data->i_new_line = 0;
    data->i_buffer = 0;
    data->simple_quote = 0;
    data->double_quote = 0;
    while (data->i_buffer < ft_strlen(data->buffer))
    {
        if (data->buffer[data->i_buffer] == '\'')
        {
            clear_quote(data, data->buffer[data->i_buffer]);
            new_line[data->i_new_line] = data->buffer[data->i_buffer];
            data->i_buffer++;
            data->i_new_line++;
            while (data->buffer[data->i_buffer] != '\'')
            {
                new_line[data->i_new_line++] = data->buffer[data->i_buffer++];
            }
            clear_quote(data, data->buffer[data->i_buffer]);
            new_line[data->i_new_line] = data->buffer[data->i_buffer];
            data->i_new_line++;
            data->i_buffer++;
        }
        else if (data->buffer[data->i_buffer] == '"')
        {
            clear_quote(data, data->buffer[data->i_buffer]);
            new_line[data->i_new_line] = data->buffer[data->i_buffer];
            data->i_buffer++;
            data->i_new_line++;
            while (data->buffer[data->i_buffer] != '"')
            {
                if (data->buffer[data->i_buffer] == '$')
                   clean_var(data, new_line);
                else
                    new_line[data->i_new_line++] = data->buffer[data->i_buffer++];
            }
            clear_quote(data, data->buffer[data->i_buffer]);
            new_line[data->i_new_line] = data->buffer[data->i_buffer];
            data->i_buffer++;
            data->i_new_line++;
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
    printf("ICI TOKEN Y : %d\n", data->token_y);
    return (new_line);
}

void    clean_token(t_data *data)
{
    int i;
    int y;

    i = 0;
    while (i < 100)
    {
        data->token[i++][0] = '\0';
    }
}

char *ft_parsing_space_quote(t_data *data)
{
    int i;
    int j;
    char    *line;

    line = gc_malloc(&data->gc , sizeof(char) * (ft_strlen(data->token[data->token_y - 1]) + 1));
    i = 0;
    j = 0;
    while (data->token[data->token_y - 1][i] == ' ')
        i++;
    while (data->token[data->token_y - 1][i])
    {
        if ((data->token[data->token_y - 1][i] == ' ' && data->token[data->token_y - 1][i + 1] == ' ') || (data->token[data->token_y - 1][i] == ' ' && data->token[data->token_y - 1][i + 1] == '\0'))
            i++;
        else
        {
            line[j] = data->token[data->token_y - 1][i];
            j++;
            i++;
        }
    }
    line[j] = '\0';
    //gc_free(&data->gc, (void **)&data->token[data->token_y - 1]);
    return (line);
}

int    fill_token_quote(t_data *data, int i)
{
    int condition;

    condition = 0;
    if (data->buffer[i] == '\'')
        condition = 1;
    else if (data->buffer[i] == '"')
        condition = 2;
    i++;
    if (condition == 1)
    {
        while (data->buffer[i] != '\'')
        {
            data->token[data->token_y][data->token_x] = data->buffer[i];
            i++;
            data->token_x++;
        }
        data->token[data->token_y][data->token_x] = '\0';
        i++;
        data->token_y++;
        data->token_x = 0;
    }
    else if (condition == 2)
    {
        while (data->buffer[i] != '\"')
        {
            data->token[data->token_y][data->token_x] = data->buffer[i];
            i++;
            data->token_x++;
        }
        data->token[data->token_y][data->token_x] = '\0';
        i++;
        data->token_y++;
        data->token_x = 0;
    }
    data->token[data->token_y - 1] = ft_parsing_space_quote(data);
    return (i);
}

void fill_token(t_data *data)
{
    int i;

    i = 0;
    data->token_x = 0;
    if (data->pipe_not_close == 0)
    {
        data->token_y = 0;
        clean_token(data);
    }
    else
        data->token_y++;
    while (data->buffer[i] != '\0')
    {
        while (!ft_is_operator(data->buffer[i]) && !ft_iswhitespace(data->buffer[i]) && data->buffer[i] != '\0')
        {
            data->token[data->token_y][data->token_x] = data->buffer[i];
            data->token_x++;
            i++;
        }
        data->token[data->token_y][data->token_x] = '\0';
        while (ft_iswhitespace(data->buffer[i]) && data->buffer[i] != '\0')
            i++;
        if (data->buffer[i] == '\0')
            return ;
        data->token_y++;
        data->token_x = 0;
        if (data->buffer[i] == '\'' || data->buffer[i] == '"')
            i = fill_token_quote(data, i);
        while (ft_is_operator(data->buffer[i]) && data->buffer[i] != '\0')
        {
            data->token[data->token_y][data->token_x] = data->buffer[i];
            data->token_x++;
            i++;
            if (!ft_is_operator(data->buffer[i]) && !ft_iswhitespace(data->buffer[i]) && data->buffer[i] != '\0')
            {
                data->token_x = 0;
                data->token_y++;
            }
        }
    }
}

void count_pipe(t_data *data)
{
    int i;

    i = 0;
    data->count_pipe = 0;
    while (data->token[i])
    {
        if (data->token[i][0] == '|')
            data->count_pipe++;
        i++;
    }
}
