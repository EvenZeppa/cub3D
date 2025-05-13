#include "cub3d.h"

int draw_ray(t_app *app, double x0, double y0, double x1, double y1, int color)
{
	double x = x0;
	double y = y0;
	double dx = x1 - x0;
	double dy = y1 - y0;
	int max;
	if (fabs(dx) > fabs(dy))
		max = fabs(dx);
	else
		max = fabs(dy);
	int i = 0;

	if (max == 0)
		return (0);
	dx /= max;
	dy /= max;
	while (i <= max)
	{
		if (my_mlx_pixel_put(app, x, y, color) < 0)
			return (1);
		x += dx;
		y += dy;
		i++;
	}
	return (0);
}
