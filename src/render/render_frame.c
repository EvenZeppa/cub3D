#include "cub3d.h"

// Fonction qui va modifier la couleur de chaque pixel
// de la fenêtre en noir pour refresh, en passant par
void	clear_frame(t_app *app)
{
	int x;
	int y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(app, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	draw_background(t_app *app);

int	render_frame(t_app *app)
{
	// Efface la fenêtre pour éviter les résidus (optionnel, dépend de ton système)
	clear_frame(app);
	if (draw_minimap(app))
		return (1);

	if (cast_ray(app)) // envoie un seul rayon dans la direction du joueur
		return (1);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);

	return (0);
}
