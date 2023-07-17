#include "minishell.h"

void    init_data(t_data *data, char **envp)
{
    data->buffer = NULL;
    data->line = NULL;
    data->parsing = NULL;
    data->bdd = NULL;
    data->env = envp;
    data->parsing_y = 0;
    data->lenquote = 0;
    data->malloc_pars = 0;
    data->i_line = 0;
    data->trace = 0;
    

    /*data->pipe_in = NULL;
    data->pipe_out = NULL;*/
   // pipe (data->tube);

   //pipe (data->tube_in);
   //pipe (data->tube_out);
}

void intHandler() {
    rl_replace_line("", 0);
    write(1, "\n", 1);
    rl_on_new_line();
    rl_redisplay();
}

void    prompt(t_data *data)
{
    signal(SIGINT, intHandler);
    signal(SIGQUIT, SIG_IGN);
    while ((data->buffer = readline("\033[0;34m#Minishell ➤ \033[0m")))
    {
        if (data->buffer[0] == 'e' && data->buffer[1] == 'x' && data->buffer[2] == 'i' && data->buffer[3] == 't')
            return ;
        if (ft_strlen(data->buffer) > 0)
        {
            add_history(data->buffer);
            ft_command(data);
            free(data->buffer);
        }
    }
    return ;
}

int	main(int argc, char **argv, char **envp)
{
    t_data data;

    init_data(&data, envp);
	prompt(&data);
}
