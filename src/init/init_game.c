#include "cub3d.h"

int	init_game(t_app *app, char *map_path)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		exit_error(app, "init mlx");
	app->win = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!app->win)
		exit_error(app, "init win");
	app->img = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!app->img)
		exit_error(app, "init img");
	app->addr = mlx_get_data_addr(app->img, &app->bpp, &app->line_length, &app->endian);
	if (!app->addr)
		exit_error(app, "init addr");
	if (parse_file(app, map_path))
		exit_error(app, "parsing");
	if (init_map(app, map_path))
		exit_error(app, "init map");
	if (init_textures(app))
		exit_error(app, "init textures");
	if (init_player(app))
		exit_error(app, "init player");
	return (0);
}
