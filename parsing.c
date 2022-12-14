#include "parsing.h"
#include "gnl_leak/get_next_line.h"

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

char    **define_info(char *info[6]) // A FREE;
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

void	*free_info(char *info[6]) //freein fo dqns toutes les erreurs;
{
	int i;

	i = 0;
	while (i < 6)
	{
		free(info[i]);
		i++;
	}
	return (NULL);
}

char **parse_file(char *file, t_data *data)
{
	int		fd;
	char	*info[6];
	int		skip_line;
	char	**map_temp;

	data->libx.txtr_w_north = NULL; //function init 
	data->libx.txtr_w_south = NULL;
	data->libx.txtr_w_east = NULL;
	data->libx.txtr_w_west = NULL;
	data->libx.texture_floor = 0;
	data->libx.texture_ceiling = 0;
	if (!verif_extension(file))
		return (NULL);
	fd = open(file, O_RDONLY);
	if (!fd)
		return (NULL);
	if (!define_info(info))
	{
		close(fd);
		return (NULL);
	}
	map_temp = search_map_info(fd, data, info);
	close(fd);
	if (!map_temp)
		return (free_info(info));
	if (!parsing_map(data, map_temp))
		return (free_info(info));
	free_info(info);
	return (data->map);
}

int main(int argc, char **argv)
{
	t_data data;
	if (argc != 2)
		return (0);
	if (!parse_file(argv[1], &data) || !data.map)
	{
		printf("Error: MAP\n");
		return (0);
	}
	printf("%s\n", data.libx.txtr_w_north);
	printf("%s\n", data.libx.txtr_w_south);
	printf("%s\n", data.libx.txtr_w_west);
	printf("%s\n", data.libx.txtr_w_east);
	printf("%d\n", data.libx.texture_floor);
	printf("%d\n", data.libx.texture_ceiling);
	printf("%d\n", data.hero.pos_x);
	printf("%d\n", data.hero.pos_y);

	free_split(data.map);
	printf("Good: MAP\n");
	return (1);
}
