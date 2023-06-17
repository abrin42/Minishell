#include "minishell.h"

void    prompt()
{
    char    *buffer;
    
    buffer = malloc(sizeof(char) * 1000);
    while ((buffer = readline("\033[0;34m#Minishell ➤ \033[0m")))
    {
        if (ft_strlen(buffer) > 0)
        {
			printf("buf:%s\n",buffer);
            ft_command(buffer);
            add_history(buffer);
        }
    }
    return ;
}

int	main()
{
	prompt();
}
