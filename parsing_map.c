#include "parsing.h"
#include "gnl_leak/get_next_line.h"

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

int put_hero(t_data *data, int i, int j)
{
    if (!verifset(data->map[i][j], "NESW"))
        return (0);
    data->hero.pos_x = i;
    data->hero.pos_y = j;
    //data->hero.dir_x =
    //data->hero.dir_y =
    //data->hero.plane_x = 0.66 * data->hero.dir_x
    //data->hero.plane_y = -0.66 * data->hero.dir_y
    data->map[i][j] = 0;
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
            put_hero(data, i, j);
			j++;
		}
		i++;
	}
	return (1);
}

int     put_map2(t_data *data, char **map_temp, int len, int height)
{
    int i;

    i = 0;
    while (i < height)
    {
        data->map[i] = (char *)malloc(sizeof(char) * len + 1);
        if (!data->map[i])
            return (0);
        data->map[i][len] = '\0';
        ft_memset(data->map[i], 32, len);
        if (map_temp[i][ft_strlen(map_temp[i]) - 1] == '\n')
            ft_strlcpy_cub(data->map[i], map_temp[i], ft_strlen(map_temp[i]));
        else
            ft_strlcpy_cub(data->map[i], map_temp[i], ft_strlen(map_temp[i]) + 1);
        i++;
    }
    return (1);
}

char    **put_map(t_data *data, char **map_temp)
{
    int i;
    int len;
    int width;

    i = 0;
    len = 0;
    width = 0;
    while(map_temp[i])
    {   
        if (ft_strlen(map_temp[i]) > len)
            len = ft_strlen(map_temp[i]);
        width++; 
        i++;
    }
    data->map = (char **)malloc(sizeof(char *) * (width + 1));
    if (!data->map)
        return (NULL);
    data->map[width] = 0;
    if (!put_map2(data, map_temp, len, width))
        return (NULL);
    return (data->map);
}

void    *parsing_map(t_data *data, char **map_temp)
{
    int i;
    char *str;
    int len;

    data->map = put_map(data, map_temp);
    if (!data->map)
    {
        free(map_temp);
        return (NULL);
    }
    if (!verif_map(data, &data->hero))
        return (NULL);
    return(data);
}