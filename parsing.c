#include "parsing.h"
#include "vgnl/get_next_line.h"

typedef struct s_hero
{
	double	pos_x;					// position de depart en x
	double	pos_y;
	double	dir_x;					// direction de depart en x
	double	dir_y;
	double	plane_x;				// demi-largeur du plan de focale en x
	double	plane_y;
}	t_hero;

typedef struct s_texture
{
	char *w_north;
    char *w_south;
    char *w_east;
    char *w_west;

	char *floor;
	char *ceiling;
}	t_texture;

typedef struct s_data
{
	char		**map;
	t_hero		*hero;
	t_texture	*texture;
}	t_data;

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

int     put_info(char *line, int ismap, t_texture *texture, char *info[6])
{
	char **new_line;

	new_line = ft_split(line, 32);
	if (!new_line)
		return (-1); // malloc
	if (ft_strncmp(new_line[0], "\n", 2))
	{
		if (ismap < 7 && !ft_strncmp(new_line[0], info[ismap], ft_strlen(info[ismap])))
            ismap++;
        else
            ismap = -1;
		if (nword(line, 32) != 2)
			ismap = -1;
	}
	free_split(new_line);
    return (ismap);
}

char    **define_info(char *info[6])
{
    int i;

    info[0] = ft_strdup("NO");
    info[1] = ft_strdup("SO");
    info[2] = ft_strdup("WE");
    info[3] = ft_strdup("EA");
    info[4] = ft_strdup("F");
    info[5] = ft_strdup("C");

    i = 0;
    while (i < 6)
    {
        if (!info[i])
            return (NULL); //malloc fail
        i++;
    }
    return (info);
}

char	*parse_info(int fd, t_texture *texture)
{
	char    *line;
	int     ismap;
    char    *info[6];

	ismap = 0;
    line = NULL;
    if (!define_info(info))
        ismap = -1;
	while (ismap >= 0)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL); //malloc fail;
		ismap = put_info(line, ismap, texture, info);
		if (ismap >= 0)
			free(line);
	}
    ismap = 0;
	while (ismap < 6)
	{
		free(info[ismap]);
		ismap++;
	}
	return (line);
}

int verif_map2(char **map, int i, int j)
{
	int len;

	len = 0;
	while(map[len])
		len++;
	if (!verifset(map[i][j], " 01NSEW"))
    {
        printf("-1\n");
		return (0);
    }
	if ((i == 0 || j == 0 || i == len - 1 || j == ft_strlen(map[i]) - 1)
		&& !verifset(map[i][j], " 1"))
    {
        printf("%c %d %d\n", map[i][j], i, j);
        printf("-2\n");
		return (0);
    }
	if (map[i][j] == ' ')
	{
		if ((i > 0 && !verifset(map[i - 1][j], " 1")) || (i < len - 1 && !verifset(map[i + 1][j], "1 ")))
        {
            printf("%c %d %d\n", map[i][j], i, j);
            printf("-3\n");
			return (0);
        }
		if ((j > 0 && !verifset(map[i][j - 1], " 1")) || (j < ft_strlen(map[i]) -1 && !verifset(map[i][j + 1], "1 ")))
        {
            printf("-4\n");
			return (0);
        }
	}
	return (1);
}

int verif_map(char **map, t_hero *hero)
{
	int i;
	int j;
	int isplayer;

	i = 0;
	isplayer = 0;
	while (map[i])
	{	
		j = 0;
		while (map[i][j] != '\0')
		{
			if (!verif_map2(map, i, j))
				return (0);
			if (verifset(map[i][j], "NSEW"))
			{
                printf("+1\n");
                hero->pos_x = j;
                hero->pos_y = i;
				isplayer++;
			}
			j++;
		}
		i++;
	}
    if (isplayer)
        return (0);
	return (1);
}

char	**parse_map(int fd, char *temp, t_hero *hero)
{
	char **map;
	char *str;
	char *fstr;

	str = get_next_line(fd);
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
	if (!verif_map(map, hero))
		return (NULL);
	return (map);
}

char    **parse_file(char *file, t_data *data)
{
    int     fd;
    char	*str;
	char	**map;

    if (verif_extension(file) == 0)
        return (NULL);
    fd = open(file, O_RDONLY);
    if (!fd)
        return (NULL);
	str = parse_info(fd, data->texture);
	if (!str) //pas de map
		return (NULL);
	map = parse_map(fd, str, data->hero);
	return (map);
}

int main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
		return (0);
	char **map = parse_file(argv[1], &data);
	if (!map)
		return (0);
	free_split(map);
}
