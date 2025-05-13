// #include "cub3d.h"

int cast_ray(t_app *app)
{
	double angle = get_player_angle(app);
	double dx = cos(angle);
	double dy = sin(angle);
	double hit_x, hit_y;

	if (perform_dda(app, dx, dy, &hit_x, &hit_y))
		return (1);

	double tile = get_minimap_tile_size(app); // à calculer comme dans draw_minimap()

	if (draw_ray(app,
			app->player.x * tile,
			app->player.y * tile,
			hit_x * tile,
			hit_y * tile,
			0xFF0000))
		return (1);
	return (0);
}
