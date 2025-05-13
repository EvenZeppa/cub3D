#include "cub3d.h"

int draw_ray(t_app *app, double x0, double y0, double x1, double y1, int color)
{
	double x = x0;
	double y = y0;
	double dx = x1 - x0;
	double dy = y1 - y0;
	double max;
	int step = 0;

	if (fabs(dx) > fabs(dy))
		max = fabs(dx);
	else
		max = fabs(dy);
	if (max == 0)
		return (0); // le rayon est un point
	dx = dx / max;
	dy = dy / max;
	while (step <= (int)max)
	{
		if (mlx_pixel_put(app->mlx, app->win, (int)x, (int)y, color) < 0)
			return (1);
		x += dx;
		y += dy;
		step++;
	}
	return (0);
}
