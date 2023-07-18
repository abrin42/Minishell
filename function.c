#include "minishell.h"

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

int ft_strlen(char  *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int	ft_strcmp2(char *s1, char *s2, int start)
{
	int	i;
	int	u;
    int g;

	u = 0;
	i = 0;
    g = 0;
    while (start != 0)
    {
        i++;
        start--;
    }
    while (ft_strlen(s2) > g)
	{
		if (s2[g] == s1[i])
			u++;
		if (s2[g] != '\0')
		{
			if (u == ft_strlen(s2))
				return (1);
		}
		i++;
        g++;
	}
	return (0);
}

char	*ft_strcpy(char *dst, char *src)
{
	int	i;
	int len;

	i = 0;
	len = ft_strlen(src);
	while (src[i] && i <  len)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] != '\0')
		{
			if (s2[i] == '\0')
			{
				return (s1[i] - s2[i]);
			}
			else
			{
				i++;
			}
		}
		if (s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}	
	}
	return (s1[i] - s2[i]);
}

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dst;
	int		len;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	dst = malloc (sizeof(char) * len + 1);
	if (dst == 0)
		return (NULL);
	while (s[i] && s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup_size(const char *s, int size,int  start)
{
	int		i;
	char	*dst;
	int		len;

	len = size;
	i = 0;	
	dst = malloc (sizeof(char) * len + 1);
	if (dst == 0)
		return (NULL);
	while (i < start)
		i++;
	while (s[i] && s[i] != '\0' && i < size + start)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char    *ft_strjoin(char *s1, char *s2)
{
    size_t    i;
    size_t    c;
    char    *str;

    if (!s1)
    {
        s1 = (char *)malloc(1 * sizeof(char));
        s1[0] = '\0';
    }
    if (!s1 || !s2)
        return (NULL);
    str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    if (str == NULL)
        return (NULL);
    i = -1;
    c = 0;
    if (s1)
        while (s1[++i] != '\0')
            str[i] = s1[i];
    while (s2[c] != '\0')
        str[i++] = s2[c++];
    str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
    return (str);
}

char	*ft_strdup_special(const char *src)
{
	char	*new;
	int		i;

	i = 0;
	while (src[i])
		i++;
	if (!(new = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (src[i] && src[i] != ' ')
	{
		new[i] = src[i];
		i++;
	}
	while (src[i])
	{
		new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strdup_var(const char *src, int i)
{
	char	*new;
	int		size;

	size = i;
	while (src[size] != '\0' && src[size] != ' ' && src[i] && src[i] != '"')
		size++;
	if (!(new = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	size = 0;
	while (src[i] && src[i] != ' ' && src[i] && src[i] != '"')
	{
		new[size] = src[i];
		i++;
		size++;
	}
	new[size] = '\0';
	return (new);
}