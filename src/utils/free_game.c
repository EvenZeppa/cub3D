#include "cub3d.h"

int	free_game(t_app *app)
{
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
		mlx_destroy_display(app->mlx);
	free(app->mlx);
	return (0);
}
