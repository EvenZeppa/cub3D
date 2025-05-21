#include "cub3d.h"

int	loop_hook(t_app *app)
{
	render_frame(app);
	return (0);
}

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
	if (ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])) == NULL)
		return (printf("Error : Invalid file extension\n"));
	if (init_game(&app, argv[1]))
		exit_error(&app, "Init app");
	if (launch_game(&app))
		exit_error(&app, "Launch app");
	if (free_game(&app))
		exit_error(&app, "Free app");
	return (0);
}
