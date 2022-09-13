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
		return (-1); // malloc
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
		if (ismap == 1 && nword(line, 32) != 2) //2 arg ? pas obligé >=3
			return (-1); //error arg info;
	}
	free_split(new_line);
    return (ismap);
}

void	parse_other_texture(t_texture_wall *w_texture, void *texture)
{
	//verif texture; 
	if (texture && nword(texture, ',') != 3)
	{
		//put default color
	}
	else
	{
		//texture == color de base; 
	}
}

char	*parse_info(int fd, t_texture_wall *w_texture)
{
	char *line;
	int ismap;

	ismap = 1;
	while (ismap == 1)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL); //malloc fail;
		ismap = put_info(line, ismap, w_texture);
		if (ismap != 0)
			free(line);
	}
	parse_other_texture(w_texture, w_texture->floor);
	return (line);
}

int verif_map2(char **map, int i, int j)
{
	int len;

	len = 0;
	while(map[len])
		len++;
	if (!verifset(map[i][j], " 01NSEW"))
		return (0);
	if ((i == 0 || j == 0 || i == len - 1 || j == ft_strlen(map[i]) - 1)
		&& !verifset(map[i][j], " 1"))
		return (0);
	if (map[i][j] == ' ')
	{
		if ((i > 0 && !verifset(map[i - 1][j], " 1")) || (i < len - 1 && !verifset(map[i + 1][j], "1 ")))
			return (0);
		if ((j > 0 && !verifset(map[i][j - 1], " 1")) || (j < ft_strlen(map[i]) -1 && !verifset(map[i][j + 1], "1 ")))
			return (0);
	}
	return (1);
}

int verif_map(char **map)
{
	int i;
	int j;
	int isplayer;

	i = 0;
	isplayer = 0;
	while (map[i])
	{	
		j = 0;
		while (map[i][j])
		{
			if (!verif_map2(map, i, j))
				return (0);
			if (verifset(map[i][j], "NSEW") && !isplayer)
			{
				isplayer = 1;
				
			}
			else if (verifset(map[i][j], "NSEW") && isplayer)
			{
				//newposition
				//ancien position = 0;
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	**parse_map(int fd, char *temp)
{
	char **map;
	char *str;
	char *fstr;

	str = get_next_line(fd); //verif si la carte peut avoir des espaces àa la fin 
	while(str != NULL)
	{
		fstr = ft_strjoin(temp, str);
		free(temp);
		free(str);
		temp = fstr;
		str = get_next_line(fd);
	}
	free(str);
	map = ft_split(temp, '\n');
	if (!verif_map(map))
		return (NULL);
	return (map);
}

char    **parse_file(char *file, t_texture_wall *w_texture)
{
    int     fd;
    char	*str;
	char	**map;

    if (verif_extension(file) == 0)
        return (NULL);
    fd = open(file, O_RDONLY);
    if (!fd)
        return (NULL);
	str = parse_info(fd, w_texture);
	if (!str) //pas de map
		return (NULL);
	map = parse_map(fd, str);
	return (map);
}

int main(int argc, char **argv)
{
    char **map;
	t_texture_wall w_texture;

    if (argc != 2)
        return (0);
    map = parse_file(argv[1], &w_texture);
    if (!map)
        return (0);
	free(map);
	system("leaks app");
}
