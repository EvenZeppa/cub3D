#include "cub3d.h"

// Callback pour render_frame (appelé à chaque itération de la loop)
int	loop_hook(t_app *app)
{
	render_frame(app);
	// if (render_frame(app))
	// 	exit_error(app, "render frame");
	return (0);
}

// Initialise les hooks et démarre la boucle principale
int	launch_game(t_app *app)
{
	mlx_hook(app->win, 2, 1L << 0, key_press, app);
	mlx_hook(app->win, 17, 0L, free_game, app);
	mlx_loop_hook(app->mlx, loop_hook, app);
	mlx_loop(app->mlx);
	return (0);
}

/** Fonction principale
	Vérifie le nombre d'arguments,
		initialise le jeu et démarre la boucle principale
	Libère la mémoire à la fin
	Retourne 0 si tout s'est bien passé,
		sinon affiche un message d'erreur **/
int	main(int argc, char *argv[])
{
	t_app	app;

	if (argc != 2)
		return (printf("Usage : ./cub3D map.cub"));
	if (init_game(&app, argv[1]))
		exit_error(&app, "Init app");
	if (launch_game(&app))
		exit_error(&app, "Launch app");
	if (free_game(&app))
		exit_error(&app, "Free app");
	return (0);
}
