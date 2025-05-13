#include "cub3d.h"

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

int cast_all_rays(t_app *app)
{
	double player_angle = get_player_angle(app);
	double tile = get_minimap_tile_size(app);
	double angle_start = player_angle - (FOV / 2.0);
	double angle_step = FOV / NUM_RAYS;

	for (int i = 0; i < NUM_RAYS; i++)
	{
		double ray_angle = angle_start + i * angle_step;
		double ray_dir_x = cos(ray_angle);
		double ray_dir_y = sin(ray_angle);
		double hit_x, hit_y;

		if (perform_dda(app, ray_dir_x, ray_dir_y, &hit_x, &hit_y) == 0)
		{
			if (draw_ray(app,
					app->player.x * tile,
					app->player.y * tile,
					hit_x * tile,
					hit_y * tile,
					0xFF0000))
				return (1);
		}
	}
	return (0);
}

