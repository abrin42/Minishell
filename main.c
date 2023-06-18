#include "minishell.h"

void    init_data(t_data *data)
{
    data->buffer = NULL;
    data->line = NULL;
    data->tab = NULL;
    data->tab_y = 0;
}

void    prompt(t_data *data)
{
    
    data->buffer = malloc(sizeof(char) * 1000);
    while ((data->buffer = readline("\033[0;34m#Minishell ➤ \033[0m")))
    {
        if (ft_strlen(data->buffer) > 0)
        {
            ft_command(data);
            add_history(data->buffer);
            free(data->buffer);
        }
    }
    return ;
}

int	main()
{
    t_data data;

    init_data(&data);
	prompt(&data);
}
