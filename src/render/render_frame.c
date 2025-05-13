#include "cub3d.h"

void	clear_frame(t_app *app);
void	draw_background(t_app *app);

int	render_frame(t_app *app)
{
	// Efface la fenêtre pour éviter les résidus (optionnel, dépend de ton système)
	mlx_clear_window(app->mlx, app->win);

	if (draw_minimap(app))
		exit_error(app, "draw minimap");

	if (cast_ray(app)) // envoie un seul rayon dans la direction du joueur
		exit_error(app, "cast ray");

	return (0);
}
