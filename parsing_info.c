#include "parsing.h"
#include "gnl_leak/get_next_line.h"

int put_info(char *line, char **info, int ismap, t_data *data)
{
	int i;
	char	**new_line;

	new_line = ft_split(line, 32);
	if (!new_line)
		return (-2);
	if (ft_strncmp(new_line[0], "\n", 2))
	{
		i = 0;
		while (i < 6)
		{
			if (!ft_strncmp(new_line[0], info[i], ft_strlen(info[i]) + 1))
			{
				if (!parse_texture(new_line[1], line, info[i], &data->libx))
                    return (-2);
                ismap = 1;
				break ;
			}
			else
				ismap = -1;
			i++;
		}
	}
	free_split(new_line);
	return (ismap);
}

char **putmap(t_data *data, int fd, char *fline)
{
    int temp;
    char *line;
    char *fstr;
    char **map_temp;

    temp = 1;
    line = 0;
    while (line || temp)
    {
        temp = 0;
        line = get_next_line(fd);
        if (!line)
            break ;
        fstr = ft_strjoin(fline, line);
        free(line);
        free (fline);
        fline = fstr;
    }
    map_temp = ft_split(fline, '\n'); //créer un split special
    if (!map_temp)
        return (NULL);
    return (map_temp);
}

int verif_info(t_libx *libx)
{
    if (!libx->txtr_w_north || !libx->txtr_w_south 
        || !libx->txtr_w_west || !libx->txtr_w_east)
        return (0);
    if (!libx->texture_floor || !libx->texture_ceiling)
        return (0);
    return (1);
}

char    **search_map_info(int fd, t_data *data, char **info)
{
	char	*line;
	int		ismap;
    char    **map_temp;

	ismap = 1;
	while (ismap >= 0)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL); //no map
		ismap = put_info(line, info, ismap, data);
        if (ismap >= 0 || ismap == -2)
            free(line);
        if (ismap == -2)
            return (NULL);
	}
    if (!verif_info(&data->libx))
        return (NULL);
	map_temp = putmap(data, fd, line);
	if (!map_temp)
        return (NULL);
    return (map_temp);
}