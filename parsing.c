#include "parsing.h"
#include "gnl_leak/get_next_line.h"

typedef struct s_texture_wall
{
	char *w_north;
    char *w_south;
    char *w_east;
    char *w_west;
}	t_texture_wall;

int verif_extension(char *file)
{
    char *extension;
    char *file_extension;

    extension = ".cub";
    file_extension = file + (strlen(file) - strlen(extension)); // REPLACE WITH FT_
    if (strncmp(file_extension, extension, strlen(extension)) != 0) // REPLACE WITH FT_
        return (0);
    return (1);
}

int     parse_info(char *line)
{
    
}

char    **parse_map(char *file)
{
    int     fd;
    char    *line;
    char    *trim_line;
    int     ismap;

    if (verif_extension(file) == 0)
        return (NULL);
    fd = open(file, O_RDONLY);
    if (!fd)
        return (NULL);
    while (fd != -1 || line != NULL)
    {
        line = get_next_line(fd);
        trim_line = ft_strtrim(line, " ");
        if (line != NULL && strncmp(trim_line, "\n", 2) != 0)  // REPLACE WITH FT_
            parse_info(trim_line);
        if (line == NULL)
            fd = -1;
        free(line);
        free(trim_line);
    }
}

int main(int argc, char **argv)
{
    char **map;

    if (argc != 2)
        return (0);
    map = parse_map(argv[1]);
    if (!map)
        return (0);
}
