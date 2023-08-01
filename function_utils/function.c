#include "../minishell.h"

void ft_putchar(char c)
{
    write(1, &c,1);
}

void ft_putstr(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	write(1, str, len);
}

unsigned int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int ft_is_operator(char c)
{
    if (c == '<' || c == '>' || c == '|')
        return (1);
    return (0);
}

int	ft_iswhitespace(char c)
{
	if ((9 <= c && c <= 13) || c == ' ')
		return (1);
	return (0);
}