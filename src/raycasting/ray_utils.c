#include "cub3d.h"

int	perform_dda(t_app *app, double ray_dir_x, double ray_dir_y, double *hit_x,
		double *hit_y)
{
	int		map_x;
	int		map_y;
	double	pos_x;
	double	pos_y;
	double	delta_x;
	double	delta_y;
	double	perp_dist;
	int side;

	map_x = (int)app->player.x;
	map_y = (int)app->player.y;
	pos_x = app->player.x;
	pos_y = app->player.y;
	delta_x = fabs(1 / ray_dir_x);
	delta_y = fabs(1 / ray_dir_y);
	int step_x, step_y;
	double side_x, side_y;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_x = (pos_x - map_x) * delta_x;
	}
	else
	{
		step_x = 1;
		side_x = (map_x + 1.0 - pos_x) * delta_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_y = (pos_y - map_y) * delta_y;
	}
	else
	{
		step_y = 1;
		side_y = (map_y + 1.0 - pos_y) * delta_y;
	}
	while (1)
	{
		if (side_x < side_y)
		{
			side_x += delta_x;
			map_x += step_x;
			side = 0; // hit vertical wall
		}
		else
		{
			side_y += delta_y;
			map_y += step_y;
			side = 1; // hit horizontal wall
		}
		if (map_x < 0 || map_y < 0 || map_x >= get_map_width(app->file_data.map)
			|| map_y >= get_map_height(app->file_data.map))
			return (1);
		if (app->file_data.map[map_y][map_x] == '1')
			break ;
	}

	// --- après la boucle, calcul de la distance perpendiculaire :
	if (side == 0)
	{
		// mur vertical touché : on corrige selon step_x
		perp_dist = (map_x - pos_x + (1 - step_x) * 0.5) / ray_dir_x;
	}
	else
	{
		// mur horizontal touché : on corrige selon step_y
		perp_dist = (map_y - pos_y + (1 - step_y) * 0.5) / ray_dir_y;
	}
	// calcul du point d'impact exact
	*hit_x = pos_x + perp_dist * ray_dir_x;
	*hit_y = pos_y + perp_dist * ray_dir_y;
	// debug
	printf("Hit wall at map (%d,%d), world (%.3f,%.3f), side=%d\n", map_x,
		map_y, *hit_x, *hit_y, side);
	return (0);
}
