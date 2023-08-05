#include "minishell.h"

void    init_data(t_data *data)
{
    data->count_path = 0;
    data->count_pipe = 0;
    data->simple_quote = 0;
    data->double_quote = 0;
    data->i_buffer = 0;
    data->i_new_line = 0;
    data->i_var = 0;
    data->condition = 1;
    data->add = 0;
    data->token_y = 0;
    data->token_x = 0;
}

/*void signal_handler(int sig)
{
        rl_replace_line("", 0);
        write(1, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
}*/

void handle_signal(int sig, siginfo_t *siginfo, void *context)
{
    t_data *data = (t_data *)siginfo->si_value.sival_ptr;

    if (sig == EOF)
    {
        gc_clean(&data->gc);
        exit (0);
    }
    else
    {
        rl_replace_line("", 0);
        write(1, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
    }
}

int test_pipe_end(t_data *data)
{
    int i;

    i = 0;
    while (data->token[i][0] != '\0')
        i++;
    if (data->token[i - 1][0] == '|')
        return(1);
    return(0);
}

void    prompt(t_data *data)
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
    data->pipe_not_close = 0;

    while ((data->buffer = readline("\033[0;34m#Minishell ➤ \033[0m")))
    {
        if (ft_strlen(data->buffer) > 0)
        {
            if (data->pipe_not_close == 0)
            {
                init_data(data);
                add_history(data->buffer);
                data->buffer = clean_buffer(data);
                if (data->simple_quote == 0 && data->double_quote == 0)
                    fill_token(data);
            }
            else
            {
                add_history(data->buffer);
                data->buffer = clean_buffer(data);
                fill_token(data);
                data->pipe_not_close--;
            }
            if (data->simple_quote != 0 || data->double_quote != 0)
                printf("A closing quotation mark is missing\n");
            else if (test_pipe_end(data) == 1)
            {
                data->pipe_not_close++;
            }
            else
            {
                count_pipe(data);
                start_command(data);
            }
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    t_data data;
    char   *shlvl_str;

    malloc_data(&data);
    init_data(&data);
    init_export_var(&data);
    data.env = envp;
    shlvl_str = getenv("SHLVL");
    shlvl_str[0] += 1;
    setenv("SHLVL", shlvl_str, 1);
    data.export = envp;
    prompt(&data);
}
