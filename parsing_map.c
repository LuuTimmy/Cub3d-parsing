#include "parsing.h"
#include "gnl_leak/get_next_line.h"

void    put_map(t_data *data, int fd)
{
    char *str;
    int i;

    i = 0;
    while (data->map[i])
    {
        str = get_next_line(fd);
        if (str[ft_strlen(str) - 1] == '\n')
            ft_strlcpy_cub(data->map[i], str, ft_strlen(str));
        else
            ft_strlcpy_cub(data->map[i], str, ft_strlen(str) + 1);
        i++;
        free(str);
    }
    close(fd);
}

int verif_map2(t_data *data, int i, int j, int len)
{
    if (!verifset(data->map[i][j], " 01NSEW"))
		return (0);
    if ((i == 0 || j == 0 || i == len - 1 || j == ft_strlen(data->map[i]) - 1)
		&& !verifset(data->map[i][j], " 1"))
		return (0);
    if (data->map[i][j] == ' ')
	{
		if (i > 0 && !verifset(data->map[i - 1][j], " 1"))
			return (0);
		if (i < len - 1 && !verifset(data->map[i + 1][j], " 1"))
			return (0);
		if (j > 0 && !verifset(data->map[i][j - 1], " 1"))
			return (0);
		if (j < ft_strlen(data->map[i]) - 1 && !verifset(data->map[i][j + 1], "1 "))
			return (0);
	}
    return (1);
}


int verif_map(t_data *data, t_hero *hero)
{
	int i;
	int j;
    int len;

	i = 0;
    len = 0;
    while (data->map[len])
        len++;
	while (data->map[i])
	{	
		j = 0;
		while (data->map[i][j])
		{
			if (!verif_map2(data, i, j, len))
				return (0);
            if (data->map[i][j] == 32)
                data->map[i][j] = '1';
			j++;
		}
		i++;
	}
	return (1);
}

void    *parsing_map(t_data *data, int fd, int skip_line)
{
    int i;
    char *str;
    int len;

    while (skip_line > 0)
    {
        str = get_next_line(fd);
        free(str);
        skip_line--;
    }
    put_map(data, fd);
    if (!verif_map(data, &data->hero))
        return (NULL);
    return(data);
}