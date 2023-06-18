#include "minishell.h"

void    init_data(t_data *data, char **envp)
{
    data->buffer = NULL;
    data->line = NULL;
    data->parsing = NULL;
    data->bdd = NULL;
    data->env = envp;
    data->parsing_y = 0;
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

int	main(int argc, char **argv, char **envp)
{
    t_data data;

    init_bdd(&data);
//---------------TEST ENV---------------//
/*int i;
i = 0;
while (envp[i])
    printf("%s\n", envp[i++]);*/
//--------------------------------------//

    init_data(&data, envp);
	prompt(&data);
}
