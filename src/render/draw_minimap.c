#include "cub3d.h"

static void	draw_tile(t_app *app, t_minimap *mm, int dx, int dy)
{
	int		tile_x;
	int		tile_y;
	char	tile;
	int		color;

	tile_x = (int)(app->player.x + dx / (double)mm->scale);
	tile_y = (int)(app->player.y + dy / (double)mm->scale);
	if (tile_y < 0 || tile_y >= get_map_height(app->file_data.map))
		return ;
	if (tile_x < 0 || tile_x >= get_map_width(app->file_data.map))
		return ;
	tile = app->file_data.map[tile_y][tile_x];
	if (tile == ' ')
		return ;
	if (tile == '1')
		color = mm->wall_color;
	else
		color = mm->floor_color;
	my_mlx_pixel_put(&app->frame, mm->center_x + dx, mm->center_y + dy, color);
}

static void	draw_minimap_background(t_app *app, t_minimap *mm)
{
	int	r2;
	int	dy;
	int	dx;

	r2 = mm->radius * mm->radius;
	dy = -mm->radius;
	dx = 0;
	while (dy <= mm->radius)
	{
		dx = -mm->radius;
		while (dx <= mm->radius)
		{
			if (dx * dx + dy * dy <= r2)
			{
				my_mlx_pixel_put(&app->frame,
					mm->center_x + dx, mm->center_y + dy, mm->background_color);
				draw_tile(app, mm, dx, dy);
			}
			dx++;
		}
		dy++;
	}
}

static void	draw_player(t_image *frame, t_minimap mm)
{
	int	r2;
	int	dy;
	int	dx;

	r2 = mm.player_radius * mm.player_radius;
	dx = 0;
	dy = -mm.player_radius;
	while (dy <= mm.player_radius)
	{
		dx = -mm.player_radius;
		while (dx <= mm.player_radius)
		{
			if (dx * dx + dy * dy <= r2)
				my_mlx_pixel_put(frame, mm.center_x + dx,
					mm.center_y + dy, mm.player_color);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_app *app)
{
	t_minimap	mm;

	mm.center_x = MINIMAP_CENTER_X;
	mm.center_y = MINIMAP_CENTER_Y;
	mm.radius = MINIMAP_RADIUS;
	mm.scale = MINIMAP_SCALE;
	mm.background_color = MINIMAP_BACKGROUND_COLOR;
	mm.wall_color = MINIMAP_WALL_COLOR;
	mm.floor_color = MINIMAP_FLOOR_COLOR;
	mm.player_color = MINIMAP_PLAYER_COLOR;
	mm.player_radius = PLAYER_CIRCLE_RADIUS;
	draw_minimap_background(app, &mm);
	draw_player(&app->frame, mm);
}
