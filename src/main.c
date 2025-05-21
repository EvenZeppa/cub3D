#include "cub3d.h"

/**
 * @brief Fonction de hook de boucle principale pour l'application.
 *
 * Cette fonction est appelée de manière répétée par la boucle
 * d'événements principale.
 * Elle est responsable du rendu d'une seule image de l'application.
 *
 * @param app Pointeur vers la structure d'état de l'application.
 * @return Retourne toujours 0.
 */
int	loop_hook(t_app *app)
{
	render_frame(app);
	return (0);
}

/**
 * @brief Lance la boucle principale du jeu et configure les hooks
 * d'événements.
 *
 * Cette fonction initialise les hooks d'événements pour la gestion
 * du clavier,
 * la fermeture de la fenêtre, le mouvement de la souris, ainsi que
 * la boucle principale
 * en utilisant la bibliothèque MiniLibX (MLX). Elle démarre ensuite
 * la boucle d'événements MLX,
 * qui maintient l'application en fonctionnement et réactive aux entrées
 * utilisateur et aux événements système.
 *
 * @param app Pointeur vers la structure d'état de l'application (t_app).
 * @return Retourne toujours 0.
 */
int	launch_game(t_app *app)
{
	mlx_hook(app->win, 2, 1L << 0, key_press, app);
	mlx_hook(app->win, 17, 0L, free_game, app);
	mlx_hook(app->win, 6, 1L << 6, mouse_move, app);
	mlx_loop_hook(app->mlx, loop_hook, app);
	mlx_loop(app->mlx);
	return (0);
}

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
