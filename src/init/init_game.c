#include "cub3d.h"

void	init_rgbs(t_app *app)
{
	app->file_data.ceiling.red = -1;
	app->file_data.ceiling.green = -1;
	app->file_data.ceiling.blue = -1;
	app->file_data.floor.red = -1;
	app->file_data.floor.green = -1;
	app->file_data.floor.blue = -1;
}

void	init_file_data(t_app *app)
{
	app->file_data.file_data = NULL;
	app->file_data.texture_north = NULL;
	app->file_data.texture_south = NULL;
	app->file_data.texture_east = NULL;
	app->file_data.texture_west = NULL;
	app->file_data.map = NULL;
}

void	init_textures_data(t_app *app)
{
	app->textures[0].img = NULL;
	app->textures[1].img = NULL;
	app->textures[2].img = NULL;
	app->textures[3].img = NULL;
}

int	init_game(t_app *app, char *map_path)
{
	app->mlx = NULL;
	app->win = NULL;
	app->img = NULL;
	app->frame.img = NULL;
	app->frame.addr = NULL;
	app->mouse_sensitivity = MOUSE_SENSITIVITY;
	app->mouse_initialized = 0;
	init_textures_data(app);
	init_rgbs(app);
	init_file_data(app);
	if (parse_file(app, map_path))
		exit_error(app, "parsing");
	app->mlx = mlx_init();
	if (!app->mlx)
		exit_error(app, "init mlx");
	app->win = mlx_new_window(app->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!app->win)
		exit_error(app, "init win");
	if (init_map(app))
		exit_error(app, "init map");
	if (init_textures(app))
		exit_error(app, "init textures");
	if (init_player(app))
		exit_error(app, "init player");
	return (0);
}
