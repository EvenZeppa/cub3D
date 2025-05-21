#include "cub3d.h"

int	init_game(t_app *app, char *map_path)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		exit_error(app, "init mlx");
	app->win = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!app->win)
		exit_error(app, "init win");
	app->frame.img = NULL;
	app->frame.addr = NULL;
	app->mouse_sensitivity = MOUSE_SENSITIVITY;
	app->mouse_initialized = 0;
	app->textures[0].img = NULL;
	app->textures[1].img = NULL;
	app->textures[2].img = NULL;
	app->textures[3].img = NULL;
	if (parse_file(app, map_path))
		exit_error(app, "parsing");
	if (init_map(app))
		exit_error(app, "init map");
	if (init_textures(app))
		exit_error(app, "init textures");
	if (init_player(app))
		exit_error(app, "init player");
	return (0);
}
