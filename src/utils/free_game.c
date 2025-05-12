#include "cub3d.h"

int	free_game(t_app *app)
{
	int	i;

	// Libération des textures
	for (i = 0; i < 4; i++)
	{
		if (app->texture[i].img)
			mlx_destroy_image(app->mlx, app->texture[i].img);
	}
	// Destruction de la fenêtre
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
		free(app->mlx);
	return (0);
}
