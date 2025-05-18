#include "cub3d.h"

static void	initialize_dda_vars(t_app *app,
		t_dda *dda, double ray_dir_x, double ray_dir_y)
{
	dda->pos_x = app->player.x;
	dda->pos_y = app->player.y;
	dda->map_x = (int)dda->pos_x;
	dda->map_y = (int)dda->pos_y;
	dda->delta_x = fabs(1 / ray_dir_x);
	dda->delta_y = fabs(1 / ray_dir_y);
}

static void	calculate_step_and_side(t_dda *dda,
		double ray_dir_x, double ray_dir_y)
{
	if (ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_x = (dda->pos_x - dda->map_x) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_x = (dda->map_x + 1.0 - dda->pos_x) * dda->delta_x;
	}
	if (ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_y = (dda->pos_y - dda->map_y) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_y = (dda->map_y + 1.0 - dda->pos_y) * dda->delta_y;
	}
}

static int	run_dda_loop(t_app *app, t_dda *dda)
{
	int	width;
	int	height;

	width = get_map_width(app->file_data.map);
	height = get_map_height(app->file_data.map);
	while (1)
	{
		if (dda->side_x < dda->side_y)
		{
			dda->side_x += dda->delta_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_y += dda->delta_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_x < 0 || dda->map_y < 0
			|| dda->map_x >= width || dda->map_y >= height)
			return (1);
		if (app->file_data.map[dda->map_y][dda->map_x] == '1')
			break ;
	}
	return (0);
}

static void	compute_dda_result(t_dda *dda,
		double ray_dir_x, double ray_dir_y, double *hit_x, double *hit_y)
{
	if (dda->side == 0)
		dda->perp_dist
			= (dda->map_x - dda->pos_x + (1 - dda->step_x) * 0.5) / ray_dir_x;
	else
		dda->perp_dist
			= (dda->map_y - dda->pos_y + (1 - dda->step_y) * 0.5) / ray_dir_y;
	*hit_x = dda->pos_x + dda->perp_dist * ray_dir_x;
	*hit_y = dda->pos_y + dda->perp_dist * ray_dir_y;
}

int	perform_dda(t_app *app,
		double ray_dir_x, double ray_dir_y, double *hit_x, double *hit_y)
{
	t_dda	dda;

	initialize_dda_vars(app, &dda, ray_dir_x, ray_dir_y);
	calculate_step_and_side(&dda, ray_dir_x, ray_dir_y);
	if (run_dda_loop(app, &dda))
		return (1);
	compute_dda_result(&dda, ray_dir_x, ray_dir_y, hit_x, hit_y);
	return (0);
}
