#include "cub3d.h"

int	cast_ray(t_app *app)
{
	double	pos[4];
	double	tile;

	pos[0] = get_player_angle(app);
	pos[1] = cos(pos[0]);
	pos[2] = sin(pos[0]);
	if (perform_dda(app, pos[1], pos[2], &pos[3], &pos[0]))
		return (1);
	tile = get_minimap_tile_size(app);
	if (draw_ray(app,
			app->player.x * tile,
			app->player.y * tile,
			pos[3] * tile,
			pos[0] * tile,
			0xFF0000))
		return (1);
	return (0);
}

int	cast_all_rays(t_app *app)
{
	double	v[4];
	double	ray_angle;
	double	hit[3];
	int		i;

	v[0] = get_player_angle(app) - (FOV / 2.0);
	v[1] = FOV / NUM_RAYS;
	i = -1;
	while (++i < NUM_RAYS)
	{
		ray_angle = v[0] + i * v[1];
		v[2] = cos(ray_angle);
		v[3] = sin(ray_angle);
		if (perform_dda(app, v[2], v[3], &hit[0], &hit[1]) == 0)
		{
			hit[3] = get_minimap_tile_size(app);
			if (draw_ray(app,
					app->player.x * hit[3],
					app->player.y * hit[3],
					hit[0] * hit[3], hit[1] * hit[3],
					0xFF0000))
				return (1);
		}
	}
	return (0);
}
