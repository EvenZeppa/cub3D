#include "cub3d.h"

static int	draw_cell(t_app *app, int x, int y, int fill_color)
{
	int	px;
	int	py;
	int	color;
	int	i;
	int	j;

	px = x * MINIMAP_TILE;
	py = y * MINIMAP_TILE;
	i = 0;
	while (i < MINIMAP_TILE)
	{
		j = 0;
		while (j < MINIMAP_TILE)
		{
			if (i == 0 || j == 0 || i == MINIMAP_TILE - 1 || j == MINIMAP_TILE - 1)
				color = 0x444444; // bordure
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

static int	draw_player(t_app *app)
{
	int	px;
	int	py;
	int	i;
	int	j;

	px = app->player.x * MINIMAP_TILE;
	py = app->player.y * MINIMAP_TILE;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (mlx_pixel_put(app->mlx, app->win, px + i, py + j, 0xFFFF00) < 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	draw_minimap(t_app *app)
{
	int	fill_color;
	int	y;
	int	x;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (app->file_data.map[y][x] == 1)
				fill_color = 0x888888;
			else
				fill_color = 0x000000;
			if (draw_cell(app, x, y, fill_color))
				return (1);
			x++;
		}
		y++;
	}
	if (draw_player(app))
		return (1);
	return (0);
}
