#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"

int cast_ray(t_app *app);
int perform_dda(t_app *app, double ray_dir_x, double ray_dir_y, double *hit_x, double *hit_y);

#endif
