#ifndef PARSING_H
#define PARSING_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_hero
{
	double	pos_x;					// position de depart en x
	double	pos_y;
	double	dir_x;					// direction de depart en x
	double	dir_y;
	double	plane_x;				// demi-largeur du plan de focale en x
	double	plane_y;
}	t_hero;

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
	char	*addr;
	int		bits_ppxl;
	int		sz_line;
	int		endian;
}	t_img;


typedef struct s_libx
{
	void	*mlx_ptr;
	void	*mlx_win;
	//t_img	txtr[4];
    t_img   *texture_wall_north;
    t_img   *texture_wall_south;
    t_img   *texture_wall_east;
    t_img   *texture_wall_west;

    int texture_floor;
    int texture_ceiling;
	t_img	*img;
}	t_libx;

typedef struct s_map_info
{   
	int ismap;

    int lenght;
    int width;
}   t_map_info;

typedef struct s_data
{
	char	**map;
	t_hero	*hero;
	t_libx	*libx;
    t_map_info   *map_info;
}	t_data;


char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *str);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
void	free_split(char **fstr);
int		nword(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int     verifset(char c, const char *set);

//parsing


//parsing_info
int	search_map_info(int fd, t_data *data, char **info);

#endif