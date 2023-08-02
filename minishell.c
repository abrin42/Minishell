#include "minishell.h"

void    init_data(t_data *data, char **envp)
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
    data->env = envp;
    data->export = envp;
    data->pipe_not_close = 0;
}
int test_pipe_end(t_data *data)
{
    int i;

    i = 0;
    while (data->token[i][0] != '\0')
        i++; 
    if (data->token[--i][0] == '|')
        return(1);
    return(0);
}
void    prompt(t_data *data)
{
    signal(SIGQUIT, SIG_IGN);
    while ((data->buffer = readline("\033[0;34m#Minishell ➤ \033[0m")))
    {
        if (ft_strlen(data->buffer) > 0)
        {
            if (data->pipe_not_close == 0)
            {
                add_history(data->buffer);
                data->buffer = clean_buffer(data);
                fill_token(data);
                count_pipe(data);
            }
            else
            {
                //printf("fin de token ?-%s- [%d]",data->token[data->token_y], data->token_y);
                fill_token(data);
                data->pipe_not_close--;
            }
            if (test_pipe_end(data) == 1)
            {
                //printf("pipe non fermer\n");
                data->pipe_not_close++;
            }
            else
                start_command(data);
        }

//*********TEST**************//
        /*int test = 0;
        while (data->token[test][0] != '\0')
            printf("===%s===\n", data->token[test++]);*/
        


    }
}

int main(int argc, char **argv, char **envp)
{
    t_data data;

    init_data(&data, envp);
    malloc_data(&data);
    init_export_var(&data);
    prompt(&data);
}