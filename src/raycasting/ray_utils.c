#include "cub3d.h"

// static void	initialize_dda_vars(t_app *app,
// 		t_dda *dda, double ray_dir_x, double ray_dir_y)
// {
// 	dda->pos_x = app->player.x;
// 	dda->pos_y = app->player.y;
// 	dda->map_x = (int)dda->pos_x;
// 	dda->map_y = (int)dda->pos_y;
// 	dda->delta_x = fabs(1 / ray_dir_x);
// 	dda->delta_y = fabs(1 / ray_dir_y);
// }

// static void	calculate_step_and_side(t_dda *dda,
// 		double ray_dir_x, double ray_dir_y)
// {
// 	if (ray_dir_x < 0)
// 	{
// 		dda->step_x = -1;
// 		dda->side_x = (dda->pos_x - dda->map_x) * dda->delta_x;
// 	}
// 	else
// 	{
// 		dda->step_x = 1;
// 		dda->side_x = (dda->map_x + 1.0 - dda->pos_x) * dda->delta_x;
// 	}
// 	if (ray_dir_y < 0)
// 	{
// 		dda->step_y = -1;
// 		dda->side_y = (dda->pos_y - dda->map_y) * dda->delta_y;
// 	}
// 	else
// 	{
// 		dda->step_y = 1;
// 		dda->side_y = (dda->map_y + 1.0 - dda->pos_y) * dda->delta_y;
// 	}
// }

// static int	run_dda_loop(t_app *app, t_dda *dda)
// {
// 	int	width;
// 	int	height;

// 	width = get_map_width(app->file_data.map);
// 	height = get_map_height(app->file_data.map);
// 	while (1)
// 	{
// 		if (dda->side_x < dda->side_y)
// 		{
// 			dda->side_x += dda->delta_x;
// 			dda->map_x += dda->step_x;
// 			dda->side = 0;
// 		}
// 		else
// 		{
// 			dda->side_y += dda->delta_y;
// 			dda->map_y += dda->step_y;
// 			dda->side = 1;
// 		}
// 		if (dda->map_x < 0 || dda->map_y < 0
// 			|| dda->map_x >= width || dda->map_y >= height)
// 			return (1);
// 		if (app->file_data.map[dda->map_y][dda->map_x] == '1')
// 			break ;
// 	}
// 	return (0);
// }

// static void	compute_dda_result(t_dda *dda,
// 		double ray_dir_x, double ray_dir_y, double *hit_x, double *hit_y)
// {
// 	if (dda->side == 0)
// 		dda->perp_dist
// 			= (dda->map_x - dda->pos_x + (1 - dda->step_x) * 0.5) / ray_dir_x;
// 	else
// 		dda->perp_dist
// 			= (dda->map_y - dda->pos_y + (1 - dda->step_y) * 0.5) / ray_dir_y;
// 	*hit_x = dda->pos_x + dda->perp_dist * ray_dir_x;
// 	*hit_y = dda->pos_y + dda->perp_dist * ray_dir_y;
// }

// // int	perform_dda(t_app *app,
// // 		double ray_dir_x, double ray_dir_y, double *hit_x, double *hit_y)
// // {
// // 	t_dda	dda;

// // 	initialize_dda_vars(app, &dda, ray_dir_x, ray_dir_y);
// // 	calculate_step_and_side(&dda, ray_dir_x, ray_dir_y);
// // 	if (run_dda_loop(app, &dda))
// // 		return (1);
// // 	compute_dda_result(&dda, ray_dir_x, ray_dir_y, hit_x, hit_y);
// // 	return (0);
// // }

// int	perform_dda(t_app *app, double ray_dir_x, double ray_dir_y, double *hit_x,
// 		double *hit_y)
// {
// 	int		map_x;
// 	int		map_y;
// 	double	pos_x;
// 	double	pos_y;
// 	double	delta_x;
// 	double	delta_y;
// 	double	perp_dist;
// 	int side;

// 	map_x = (int)app->player.x;
// 	map_y = (int)app->player.y;
// 	pos_x = app->player.x;
// 	pos_y = app->player.y;
// 	delta_x = fabs(1 / ray_dir_x);
// 	delta_y = fabs(1 / ray_dir_y);
// 	int step_x, step_y;
// 	double side_x, side_y;
// 	if (ray_dir_x < 0)
// 	{
// 		step_x = -1;
// 		side_x = (pos_x - map_x) * delta_x;
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		side_x = (map_x + 1.0 - pos_x) * delta_x;
// 	}
// 	if (ray_dir_y < 0)
// 	{
// 		step_y = -1;
// 		side_y = (pos_y - map_y) * delta_y;
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		side_y = (map_y + 1.0 - pos_y) * delta_y;
// 	}
// 	while (1)
// 	{
// 		if (side_x < side_y)
// 		{
// 			side_x += delta_x;
// 			map_x += step_x;
// 			side = 0; // hit vertical wall
// 		}
// 		else
// 		{
// 			side_y += delta_y;
// 			map_y += step_y;
// 			side = 1; // hit horizontal wall
// 		}
// 		if (map_x < 0 || map_y < 0 || map_x >= get_map_width(app->file_data.map)
// 			|| map_y >= get_map_height(app->file_data.map))
// 			return (1);
// 		if (app->file_data.map[map_y][map_x] == '1')
// 		{
// 			// printf("Hit wall at (%d, %d)\n", map_x, map_y);
// 			break ;
// 		}
// 	}
// 	// --- après la boucle, calcul de la distance perpendiculaire :
// 	if (side == 0)
// 	{
// 		// mur vertical touché : on corrige selon step_x
// 		perp_dist = (map_x - pos_x + (1 - step_x) * 0.5) / ray_dir_x;
// 	}
// 	else
// 	{
// 		// mur horizontal touché : on corrige selon step_y
// 		perp_dist = (map_y - pos_y + (1 - step_y) * 0.5) / ray_dir_y;
// 	}
// 	// calcul du point d'impact exact
// 	*hit_x = pos_x + perp_dist * ray_dir_x;
// 	*hit_y = pos_y + perp_dist * ray_dir_y;
// 	return (0);
// }

double perform_dda_3d(
	char **map,
	int map_width,
	int map_height,
	double pos_x,
	double pos_y,
	double ray_dir_x,
	double ray_dir_y,
	int *side,
	double *hit_x,
	double *hit_y
)
{
	int map_x = (int)pos_x;
	int map_y = (int)pos_y;

	double delta_x = fabs(1.0 / ray_dir_x);
	double delta_y = fabs(1.0 / ray_dir_y);

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
			*side = 0;
		}
		else
		{
			side_y += delta_y;
			map_y += step_y;
			*side = 1;
		}

		// sécurité : sortir si en dehors des limites
		if (map_x < 0 || map_y < 0 || map_x >= map_width || map_y >= map_height)
			return (-1.0); // erreur

		if (map[map_y][map_x] == '1')
			break;
	}

	// distance perpendiculaire
	double perp_dist;
	if (*side == 0)
		perp_dist = (map_x - pos_x + (1 - step_x) * 0.5) / ray_dir_x;
	else
		perp_dist = (map_y - pos_y + (1 - step_y) * 0.5) / ray_dir_y;

	// coordonnées du point d'impact dans le monde
	if (hit_x && hit_y)
	{
		*hit_x = pos_x + perp_dist * ray_dir_x;
		*hit_y = pos_y + perp_dist * ray_dir_y;
	}

	return perp_dist;
}

