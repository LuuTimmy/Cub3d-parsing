#include "parsing.h"
#include "gnl_leak/get_next_line.h"

int verif_info(char **newline, char *line, char **info)
{

}

int put_info(char *line, char **info, int ismap)
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
				verif_info(new_line, line, info);
				ismap++;
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

int put_size_map2(t_data *data, int length, int height)
{
    int i;

    i = 0;
    data->map = malloc(sizeof(char *) * height + 1);
    if (data->map == NULL)
        return (0);
    while (i < height)
    {
        data->map[i] = malloc(sizeof(char) * length + 1);
        if (!data->map[i])
        {
            free_split(data->map);
            return (0); //malloc error;
        }
        memset(data->map[i], ' ', length);  //remplace with ft_
        i++;
    }
    return (1);
}

int put_size_map(t_data *data, int fd, char *line) //strtrim right pour plus d'opti
{
    int max_length;
    int height;
    int i;

    i = 0;
    height = 0;
    max_length = ft_strlen(line);
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        if (line && ft_strlen(line) > max_length)
            max_length = ft_strlen(line);
        height++; //espace + \n à la fin du fichier pour plus d'opti;
    }
    free(line);
    i = put_size_map2(data, max_length, height);
    return (i);
}

int	search_map_info(int fd, t_data *data, char **info)
{
	char	*line;
	int		ismap;
    int     nb_line;

	ismap = 0;
    nb_line = 0;
    line = get_next_line(fd);
	while (ismap >= 0)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			return (-1); //no map
		ismap = put_info(line, info, ismap);
        nb_line++;
	}
    //verif_info si y'a tout les élements
	if (!put_size_map(data, fd, line))
		return (-1);
    if (nb_line == 0)
        return (0);
    return (nb_line - 1);
}