#include "cub3d.h"

/* Fonction pour liberer les donnees sur la heap */
int	free_game(t_app *app)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (app->texture[i].img)
			mlx_destroy_image(app->mlx, app->texture[i].img);
	}
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	return (0);
}
