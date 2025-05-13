#include "cub3d.h"

int	get_map_width(char **map)
{
	int max = 0;
	int i = 0;
	while (map[i])
	{
		int len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	get_map_height(char **map)
{
	int i = 0;
	while (map[i])
		i++;
	return (i);
}

double get_player_angle(t_app *app)
{
	double angle;

	angle = atan2(app->player.dir_y, app->player.dir_x);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

double get_minimap_tile_size(t_app *app)
{
	int w = get_map_width(app->file_data.map);
	int h = get_map_height(app->file_data.map);
	int max = (w > h) ? w : h;
	return ((double)MINIMAP_SIZE / (double)max);
}

int my_mlx_pixel_put(t_app *app, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = app->addr + (y * app->line_length + x * (app->bpp
					/ 8));
		*(unsigned int *)dst = color;
	}
	return (0);
}
