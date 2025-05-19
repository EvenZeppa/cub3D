#include "cub3d.h"

/* Recupere la largeur d'une map donnee */
int	get_map_width(char **map)
{
	int	max;
	int	i;
	int	len;

	max = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

/* Recupere la hauteur d'une map donnee */
int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

/* Renvoie l'angle du joueur en fonction de sa direction en x et y */
double	get_player_angle(t_app *app)
{
	double	angle;

	angle = atan2(app->player.dir_y, app->player.dir_x);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

/* Renvoie la taille des cellules en fonction de la map */
double	get_minimap_tile_size(t_app *app)
{
	int	w;
	int	h;
	int	max;

	w = get_map_width(app->file_data.map);
	h = get_map_height(app->file_data.map);
	if (w > h)
		max = w;
	else
		max = h;
	return ((double)MINIMAP_SIZE / (double)max);
}

/* Fonction qui remplace la fonction mlx de base pour imprimer des pixels */
void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return;

	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

