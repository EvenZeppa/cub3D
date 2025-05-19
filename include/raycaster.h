#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"

int cast_ray(t_app *app);
int perform_dda(t_app *app, double ray_dir_x, double ray_dir_y, double *hit_x, double *hit_y);
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
);
#endif
