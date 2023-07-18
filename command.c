#include "minishell.h"

void    ft_echo(t_data *data, int i)
{
    if (data->parsing[data->parsing_y + 1] != NULL)
        ft_putstr(data->parsing[data->parsing_y + 1]);
    write(1, "\n", 1);
}

void    ft_pwd(t_data *data)
{
    char    *str;
    char    *pwd;

    str = malloc(sizeof(char) * 500);
    pwd = malloc(sizeof(char) * 500);
    str = NULL;
    pwd = NULL;
    pwd = getcwd(str, 100);
    ft_putstr(pwd);
    ft_putchar('\n');
    free(str);
    free(pwd);
}

void ft_cd(t_data *data)
{
    printf("ICI Y : %s\n", data->parsing[data->parsing_y + 1]);
    chdir(data->parsing[data->parsing_y + 1]);
}

void    ft_env(t_data *data)
{
    int i;

    i = 0;
    while (data->env[i])
        printf("%s\n", data->env[i++]);
}

void    ft_exit(t_data *data)
{
    free_parsing(data);
    exit (0);
}

void    init_export_var(t_data *data)
{
    int i;

    i = 0;
    data->export_var = malloc(sizeof(char *) * 1000);
}

void    tri_export(t_data *data)
{
    int i;
    int y;
    char *temp;

    i = 0;
    y = 0;
    temp = malloc(sizeof(char) * 1000);
    while (data->export[i + 1])
    {
        y = i + 1;
        if (data->export[i][0] > data->export[y][0])
        {
            temp = data->export[i];
            data->export[i] = data->export[y];
            data->export[y] = temp;
            i = 0;
        }
        i++;
    }
    temp = NULL;
    free(temp);
    }

void    tri_export_var(t_data *data)
{
    int i;
    int y;
    char *temp;

    i = 0;
    y = 0;
    temp = malloc(sizeof(char) * 1000);
    while (data->export_var[i + 1])
    {
        y = i + 1;
        if (data->export_var[i][0] > data->export_var[y][0])
        {
            temp = data->export_var[i];
            data->export_var[i] = data->export_var[y];
            data->export_var[y] = temp;
            i = 0;
        }
        i++;
    }
    temp = NULL;
    free(temp);
}

void	clean_result_export_var(t_data *data, int i)
{
	int	y;
	char	temp;
	
	y = 0;
	while (data->export_var[i][y] != '=' && data->export_var[i][y] != '\0')
		y++;
	if (data->export_var[i][y] == '=')
	{
		while(data->export_var[i][y])
			y++;
		data->export_var[i][y + 2] = '\0';
		data->export_var[i][y + 1] = '"';
		while(data->export_var[i][y] != '=')
		{
			data->export_var[i][y] = data->export_var[i][y - 1];
			y--;
		}
		y++;
		data->export_var[i][y] = '"';
	}
	else
	{
		data->export_var[i][y] = '=';
		data->export_var[i][y + 1] = '\'';
		data->export_var[i][y + 2] = '\'';
		data->export_var[i][y + 3] = '\0';
	}
}

int	ft_strcmp_export_var(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] != '\0')
		{
			if (s2[i] == '\0')
				return (s1[i] - s2[i]);
			else
				i++;
		}
		if (s1[i] == '\0')
			return (0);
		else if (s1[i] == '=' && s2[i] == '=')
			return (1);
	}
	return (s1[i] - s2[i]);
}

int	ft_strcmp_unset(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] != '\0')
		{
			if (s2[i] == '\0')
				return (s1[i] - s2[i]);
			else
				i++;
		}
	}
	if (s2[i] == '=' && s1[i] == '\0')
		return (1);
	return (s1[i] - s2[i]);
}

void    ft_export(t_data *data)
{
    int i;
    int y;

    i = 0;
    y = 0;
    if (data->parsing[data->parsing_y + 1] != NULL)
    {
        while (data->export_var[i])
        {
        	if (ft_strcmp_export_var(data->parsing[data->parsing_y + 1], data->export_var[i]) == 0)
        		return ;
        	else if(ft_strcmp_export_var(data->parsing[data->parsing_y + 1], data->export_var[i]) == 1)
        		break ;
            i++;
        }
        data->export_var[i] = ft_strdup_special(data->parsing[data->parsing_y + 1]);
        clean_result_export_var(data, i);
    }
    else
    {
        tri_export(data);
        tri_export_var(data);
        i = 0;
        while (data->export[i])
            printf("declare -x %s\n", data->export[i++]);
        i = 0;
        while (data->export_var[i])
        {
            if (data->export_var[i][0] != '\0')
                printf("declare -x %s\n", data->export_var[i]);
            i++;
        }
    }
}

void    reset_var(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        str[i] = '\0';
        i++;
    }
}

void    ft_unset(t_data *data)
{
    int i;

    i = 0;
    while(data->export_var[i])
    {
        if (ft_strcmp_unset(data->parsing[data->parsing_y + 1], data->export_var[i]) == 1)
        {
            reset_var(data->export_var[i]);
            return ;
        }
        i++;
    }
}

int command_terminal (t_data *data)
{
    char    **args;
    char    *path;
    int     i;
    int     stop_condition;
    int status;
    __pid_t pid;
    int v;

    pid = fork();
    if (pid == -1)
    {
        //perror("fork");
        //bash: fork : no such file 
        // put_error(strerror(errno), file)
        write (2, "Erreur lors de la création du processus.\n", 41); // demander a noah si la sortie 2 c'est good  
        //printf("Erreur lors de la création du processus.\n");
        return (0);
    }
    else if (pid == 0)
    {
        //args = malloc_args(data, args);
        //malloc_bdd(data);
        i = 0;
        /*for (int y = 0; data->parsing[y] != NULL; y++)
            printf("===%s===\n", data->parsing[y]);*/
        //printf("-+-\n");
        while (data->bdd[i] != NULL )
        {
            stop_condition = 0;
            path = ft_strjoin(data->bdd[i], data->parsing[data->parsing_y]); //attention data->parsing[0] echo | ls = ls
            //args = malloc_args(data, args, path);
            //args[1] = ft_strdup(data->parsing[data->parsing_y + 1]);
            //if (!(data->parsing[data->parsing_y + 1][0]))
            //printf("-+***-\n");
            args = malloc(sizeof (char*) * 2);
            args[0] = ft_strdup(path);
            args[1] = NULL;
            stop_condition = execve(path, args, data->env);
            free(path);
            free(args[0]);
            free(args[1]);
            free(args);
            /*v = 0;
            while (args[v])
            {
                free(args[v]);
                v++;
            }
            free(args);*/
            i++;
        }
    }
    waitpid(pid, &status, 0);
    if (stop_condition != -1)
        return (1);
    return (0);
}