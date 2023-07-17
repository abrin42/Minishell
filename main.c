#include "minishell.h"

void    init_data(t_data *data, char **envp)
{
    data->buffer = NULL;
    data->line = NULL;
    data->parsing = NULL;
    data->bdd = NULL;
    data->env = envp;
    data->export = envp;
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

char    *clean_buffer(t_data *data)
{
    char    *new_line;
    char    *intact_line;

    new_line = malloc(sizeof(char) * 10000);
    intact_line = ft_strdup(data->buffer);
    data->i_new_line = 0;
    data->i_buffer = 0;
printf("BUFFER1 ===%s===\n", data->buffer);
    clear_quote(data);
    printf("data->i_buffer : %d\n", data->i_buffer);
    while (data->i_buffer < ft_strlen(data->buffer))
    {
        if (data->buffer[data->i_buffer] == '\'')
        {
            data->i_buffer++;
            while (data->buffer[data->i_buffer] != '\'')
            {
                new_line[data->i_new_line++] = data->buffer[data->i_buffer++];
                printf("ICI : %c et %c\n", new_line[data->i_new_line - 1], data->buffer[data->i_buffer]);
            }
        }
        else if (data->buffer[data->i_buffer] == '"')
        {
            data->i_buffer++;
            while (data->buffer[data->i_buffer] != '"')
            {
                if (data->buffer[data->i_buffer] == '$')
                    clean_var(data, new_line);
                new_line[data->i_new_line++] = data->buffer[data->i_buffer++];
                printf("ICI : %c et %c\n", new_line[data->i_new_line - 1], data->buffer[data->i_buffer]);
            }
        }
        else if (data->buffer[data->i_buffer] == '$')
        {
            clean_var(data, new_line);
        }
        else if (data->buffer[data->i_buffer] == '\\')
        {
            printf("OUIOUIICI\n");
            new_line[data->i_new_line++] = ' ';
        }
        else
        {
            new_line[data->i_new_line++] = data->buffer[data->i_buffer];
        }
        printf("ICI : %c et %d\n", data->buffer[data->i_buffer], data->i_buffer);
        data->i_buffer++;
    }
    new_line[data->i_new_line] = '\0';
    free(data->buffer);
    printf("BUFFER1.5 ===%s=== et %d\n", new_line, data->i_buffer);
    return (new_line);
}

void intHandler()
{
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
        if (ft_strlen(data->buffer) > 0)
        {
            add_history(data->buffer);

printf("DATA_BUFFER ===%s=== et %d\n", data->buffer, ft_strlen(data->buffer));
            data->buffer = clean_buffer(data);
            if (data->simple_quote % 2 == 1 || data->double_quote % 2 == 1)
            {
               printf("You need to close our quote !\n");
            }
            else
            {
            if (data->buffer[0] == 'e' && data->buffer[1] == 'x' && data->buffer[2] == 'i' && data->buffer[3] == 't')
                return ;
printf("BUFFER2 ===%s===\n", data->buffer);
            ft_command(data);
            free(data->buffer);
            }
        }
    }
    return ;
}

int	main(int argc, char **argv, char **envp)
{
    t_data data;

    init_data(&data, envp);
    init_export_var(&data);
	prompt(&data);
}
