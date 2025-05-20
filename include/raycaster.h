#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"

// Performs the 3D Digital Differential Analyzer (DDA) algorithm for raycasting.
// Returns the distance to the wall hit.
double	perform_dda_3d(t_dda *d);

// Computes information for a single ray, such as direction and intersection.
void	compute_ray_info(t_app *app, t_ray *ray, int i, double base_angle);

#endif
