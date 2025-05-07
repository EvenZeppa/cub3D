#include "cub3d.h"

// Callback pour render_frame (appelé à chaque itération de la loop)
int	loop_hook(t_app *app)
{
	render_frame(app);
	return (0);
}

// Initialise les hooks et démarre la boucle principale
int	launch_game(t_app *app)
{
	// Hook pour les entrées clavier (appui)
	mlx_hook(app->win, 2, 1L << 0, key_press, app);
	// Hook pour les entrées clavier (relâchement)
	mlx_hook(app->win, 3, 1L << 1, key_release, app);
	// Hook pour la fermeture de la fenêtre (croix rouge)
	mlx_hook(app->win, 17, 0L, free_game, app);
	// Hook pour le rendu à chaque frame
	mlx_loop_hook(app->mlx, loop_hook, app);
	// Boucle principale MinilibX
	mlx_loop(app->mlx);
}

int	main(int argc, char *argv[])
{
	t_app	app;

	if (argc != 2)
		return (printf("Usage : ./cub3D map.cub"));
	if (init_game(&app, argv[1]))
		exit_error(app, "Init app");
	if (launch_game(&app))
		exit_error(app, "Launch app");
	if (free_game(&app))
		exit_error(app, "Free app");
	return (0);
}
