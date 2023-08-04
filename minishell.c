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

/*void signal_handler(int sig)
{
    if (sig == EOF)
    {
        gc_clean();
    }
    else
    {
        rl_replace_line("", 0);
        write(1, "\n", 1);
        rl_on_new_line();
        rl_redisplay();
    }
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

void    prompt(t_data *data)
{
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
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
