#include "cub3d.h"

int perform_dda(t_app *app, double ray_dir_x, double ray_dir_y, double *hit_x, double *hit_y)
{
	int map_x = (int)app->player.x;
	int map_y = (int)app->player.y;
	double pos_x = app->player.x;
	double pos_y = app->player.y;

	double delta_x = fabs(1 / ray_dir_x);
	double delta_y = fabs(1 / ray_dir_y);

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
		}
		else
		{
			side_y += delta_y;
			map_y += step_y;
		}

		if (map_x < 0 || map_y < 0 || map_x >= get_map_width(app->file_data.map)
			|| map_y >= get_map_height(app->file_data.map))
			return (1);
		if (app->file_data.map[map_y][map_x] == '1')
			break;
	}

	// Calcul du point d’impact exact
	if (side_x < side_y)
	{
		*hit_x = pos_x + (side_x - delta_x) * ray_dir_x;
		*hit_y = pos_y + (side_x - delta_x) * ray_dir_y;
	}
	else
	{
		*hit_x = pos_x + (side_y - delta_y) * ray_dir_x;
		*hit_y = pos_y + (side_y - delta_y) * ray_dir_y;
	}
	return (0);
}
