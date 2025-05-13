#include "cub3d.h"

int cast_ray(t_app *app)
{
	double angle = get_player_angle(app);
	double dx = cos(angle);
	double dy = sin(angle);
	double hit_x;
	double hit_y;

	if (perform_dda(app, dx, dy, &hit_x, &hit_y))
		return (1);
	if (draw_ray(app,
		app->player.x * TILE_SIZE,
		app->player.y * TILE_SIZE,
		hit_x * TILE_SIZE,
		hit_y * TILE_SIZE,
		0xFF0000))
		return (1);
	return (0);
}
