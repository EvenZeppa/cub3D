#include "cub3d.h"

static int	draw_cell(t_app *app, int x, int y, int fill_color, double tile)
{
	int px;
	int py;
	int i;
	int j;
	int color;

	if ((int)tile < 1)
		return (1); // sécurité : tile trop petit, on ne dessine pas

	px = x * tile;
	py = y * tile;
	i = 0;
	while (i < (int)tile)
	{
		j = 0;
		while (j < (int)tile)
		{
			if (i == 0 || j == 0 || i == (int)tile - 1 || j == (int)tile - 1)
				color = 0x444444;
			else
				color = fill_color;
			if (mlx_pixel_put(app->mlx, app->win, px + i, py + j, color) < 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	draw_player(t_app *app, double tile)
{
	int	px = app->player.x * tile;
	int	py = app->player.y * tile;
	int	size;
	int	i;
	int	j;

	// Taille du joueur affiché : entre 2 et tile/4 max
	size = tile / 4;
	if (size < 2)
		size = 2;

	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			if (mlx_pixel_put(app->mlx, app->win, px + i, py + j, 0xFFFF00) < 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int draw_minimap(t_app *app)
{
	int x, y, fill_color;
	int map_w = get_map_width(app->file_data.map);
	int map_h = get_map_height(app->file_data.map);
	int max_dim = map_w > map_h ? map_w : map_h;
	double tile = (double)MINIMAP_SIZE / (double)max_dim;

	y = -1;
	while (app->file_data.map[++y])
	{
		x = -1;
		while (app->file_data.map[y][++x])
		{
			if (app->file_data.map[y][x] == ' ')
				continue;
			if (app->file_data.map[y][x] == '1')
				fill_color = 0x888888;
			else
				fill_color = 0x000000;
			if (draw_cell(app, x, y, fill_color, tile))
				return (1);
		}
	}
	if (draw_player(app, tile))
		return (1);
	return (0);
}
