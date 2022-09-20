#include "parsing.h"
#include "gnl_leak/get_next_line.h"

int    put_texture(char *path, char **texture)
{   
    *texture = ft_strtrim(path, "\n");
    if (!*texture)
        return (0);
    return (1);
}

int verif_is_digit(char **str)
{
    int i;
    int j;

    i = 0;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if ((str[i][j] < '0' || str[i][j] > '9') && str[i][j] != '\n')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

unsigned int parse_color(char **color_split)
{

    int is_false;
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    if (!verif_is_digit(color_split))
        return (0);
    red = ft_atoi_v(color_split[0], &is_false);
    if (red > 255 || is_false == 1)
        return (0);
    green = ft_atoi_v(color_split[1], &is_false);
    if (green > 255 || is_false == 1)
        return (0);
    blue = ft_atoi_v(color_split[2], &is_false);
    if (blue > 255 || is_false == 1)
        return (0);
    return ((red * 256 * 256) + (green * 256) + blue);
}

int put_color(char *color_rgb, unsigned int *color)
{   
    int i;
    char **color_split;

    if (nword(color_rgb,',') != 3 || count_char(color_rgb, ',' != 2))
        return (0);
    color_split = ft_split(color_rgb, ',');
    if (!color_split)
        return (0);
    *color = parse_color(color_split);
    if (*color == 0)
    {
        free_split(color_split);
        return (0);
    }
    free_split(color_split);
    return (1);
}

int parse_texture(char *newline, char *line, char *info, t_libx *lx)
{
    int temp;

    if (nword(line, 32) != 2)
        return (0);
    if (!ft_strncmp(info, "NO", 3) && !lx->txtr_w_north)
        temp = put_texture(newline, &lx->txtr_w_north);
    else if (!ft_strncmp(info, "SO", 3) && !lx->txtr_w_south && lx->txtr_w_north)
        temp = put_texture(newline, &lx->txtr_w_south);
    else if (!ft_strncmp(info, "WE", 3) && !lx->txtr_w_west && lx->txtr_w_south)
        temp = put_texture(newline, &lx->txtr_w_west);
    else if (!ft_strncmp(info, "EA", 3) && !lx->txtr_w_east && lx->txtr_w_west)
        temp = put_texture(newline, &lx->txtr_w_east);
    else if (!ft_strncmp(info, "F", 2) && !lx->texture_floor && lx->txtr_w_east)
        temp = put_color(newline, &lx->texture_floor);
    else if (!ft_strncmp(info, "C", 2) && !lx->texture_ceiling && lx->texture_floor)
        temp = put_color(newline, &lx->texture_ceiling);
    else
        return (0);
    if(!temp)
        return (0);
    return (1);
}