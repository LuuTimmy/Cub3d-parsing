#include "parsing.h"
#include "gnl_leak/get_next_line.h"

typedef struct s_texture_wall
{
	char *w_north;
    char *w_south;
    char *w_east;
    char *w_west;

	char *floor;
	char *ceiling;
}	t_texture_wall;

int verif_extension(char *file)
{
    char *extension;
    char *file_extension;

    extension = ".cub";
    file_extension = file + (ft_strlen(file) - ft_strlen(extension));
    if (ft_strncmp(file_extension, extension, ft_strlen(extension)) != 0) 
        return (0);
    return (1);
}

int     put_info(char *line, int ismap, t_texture_wall *w_texture)
{
	char **new_line; //fuck norme

	new_line = ft_split(line, 32);
	if (!new_line)
		return (-1);	
	if (ft_strncmp(new_line[0], "\n", 2))
	{
		if (!ft_strncmp(new_line[0], "NO", 3))
			w_texture->w_north = new_line[1];
		else if (!ft_strncmp(new_line[0], "SO", 3))
			w_texture->w_south = new_line[1];
		else if (!ft_strncmp(new_line[0], "WE", 3))
			w_texture->w_west = new_line[1];
		else if (!ft_strncmp(new_line[0], "EA", 3))
			w_texture->w_east = new_line[1];
		else if (!ft_strncmp(new_line[0], "F", 2))
			w_texture->floor = new_line[1];
		else if (!ft_strncmp(new_line[0], "C", 2))
			w_texture->ceiling = new_line[1];
		else
			ismap = 0;
		if (ismap == 1 && nword(line, 32) != 2)
			return (-1); //error arg info;
	}
	free_split(new_line);
    return (ismap);
}

int parse_info(int fd, t_texture_wall *w_texture)
{
	char *line;
	int ismap;
	int nb_line_info;

	ismap = 1;
	nb_line_info = 0;
	while (ismap == 1)
	{
		line = get_next_line(fd);
		if (!line)
			return (-1); //malloc fail;
		ismap = put_info(line, ismap, w_texture);
		free(line);
		nb_line_info++;
	}
	//verif info;
	return (nb_line_info);
}

int	countbit(char *argv)
{
	char	buff[1];
	int		nbbit;

	nbbit = 0;
	while (read(fd, buff, 1) > 0)
		nbbit++;
	return (nbbit);
}

char	**parse_map(int fd, int nb_line_info)
{
	char **map;
	char *str;

	while(nb_line_info > 0)
	{
		str = get_next_line(fd);
		printf("%s", str);
		nb_line_info--;
		free(str);
	}
	
	
}

char    **parse_file(char *file, t_texture_wall *w_texture)
{
    int     fd;
    int     nb_line_info;
	char	**map;

	nb_line_info = 0;
    if (verif_extension(file) == 0)
        return (NULL);
    fd = open(file, O_RDONLY);
    if (!fd)
        return (NULL);
	nb_line_info = parse_info(fd, w_texture);
	if (nb_line_info < 0)
		return (NULL);
	close(fd);
	fd = open(file, O_RDONLY);
    if (!fd)
        return (NULL);
	map = parse_map(fd, nb_line_info - 1);
	return (map);
}

int main(int argc, char **argv)
{
    char **map;
	t_texture_wall w_texture;

    if (argc != 2)
        return (0);
    map = parse_file(argv[1], &w_texture);
    // if (!map)
    //     return (0);
}
