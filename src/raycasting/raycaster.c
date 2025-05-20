#include "cub3d.h"

static void	init_dda_data(t_app *app, t_ray *ray, t_dda *dda)
{
	dda->map = app->file_data.map;
	dda->map_width = get_map_width(app->file_data.map);
	dda->map_height = get_map_height(app->file_data.map);
	dda->pos_x = app->player.x;
	dda->pos_y = app->player.y;
	dda->dir_x = ray->dir_x;
	dda->dir_y = ray->dir_y;
}

static void	fill_ray_from_dda(t_ray *ray, t_dda *dda, double base_angle)
{
	if (dda->dist < 0)
		ray->dist = 0.0001;
	else
		ray->dist = dda->dist;
	ray->side = dda->side;
	ray->hit_x = dda->hit_x;
	ray->hit_y = dda->hit_y;
	ray->corrected_dist = ray->dist * cos(ray->angle - base_angle);
	if (ray->corrected_dist < 0.0001)
		ray->corrected_dist = 0.0001;
	ray->wall_height = (int)(WIN_HEIGHT / ray->corrected_dist);
	ray->draw_start = -ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	compute_ray_info(t_app *app, t_ray *ray, int i, double base_angle)
{
	t_dda	dda;

	ray->angle = base_angle - (FOV / 2) + ((double)i / NUM_RAYS) * FOV;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	init_dda_data(app, ray, &dda);
	dda.dist = perform_dda_3d(&dda);
	fill_ray_from_dda(ray, &dda, base_angle);
	ray->screen_x = i * (WIN_WIDTH / NUM_RAYS);
}
