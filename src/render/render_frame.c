#include "cub3d.h"

void	clear_frame(t_app *app);
void	draw_background(t_app *app);

void	render_frame(t_app *app)
{
	int	x;

	clear_frame(app);
	draw_background(app);
	x = 0;
	while (x < WIN_WIDTH - 1)
	{
		cast_ray(app, x, WIN_HEIGHT / 2);
	}
	// mlx_put_image_to_window(app->mlx, app->win, app->img_ptr, 0, 0);
	draw_minimap(app);
}
