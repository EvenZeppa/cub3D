#include "cub3d.h"

/* Fonction pour liberer les donnees sur la heap */
int free_game(t_app *app)
{
	int i;

	if (!app)
		return (1);
	i = 0;
	while (i < 4)
	{
		if (app->textures[i].img)
			mlx_destroy_image(app->mlx, app->textures[i].img);
		i++;
	}
	if (app->frame.img)
		mlx_destroy_image(app->mlx, app->frame.img);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	return (exit(0), 0);
}

