#include "minishell.h"

void    init_data(t_data *data)
{
    data->token_x = 0;
    data->token_y = 0;
    data->count_path = 0;
    data->count_pipe = 0;
    data->simple_quote = 0;
    data->double_quote = 0;
    data->i_buffer = 0;
    data->i_new_line = 0;
    data->i_var = 0;
    data->condition = 1;
    data->add = 0;
}

void    prompt(t_data *data)
{
    signal(SIGQUIT, SIG_IGN);
    while ((data->buffer = readline("\033[0;34m#Minishell ➤ \033[0m")))
    {
        init_data(data);
        init_export_var(data);
        if (ft_strlen(data->buffer) > 0)
        {
            add_history(data->buffer);
            data->buffer = clean_buffer(data);
            fill_token(data);
            count_pipe(data);
            start_command(data);
        }

//*********TEST**************//
/*int test = 0;
while (data->token[test][0] != '\0')
{
    printf("===%s===\n", data->token[test++]);
}*/

    }
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    init_data(&data);
    malloc_data(&data);
    init_export_var(&data);
    data.env = envp;
    data.export = envp;
    prompt(&data);
}
