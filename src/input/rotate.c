#include "cub3d.h"

void	rotate_left(t_app *app)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(-app->player.rotate_speed) - app->player.dir_y * sin(-app->player.rotate_speed);
	app->player.dir_y = old_dir_x * sin(-app->player.rotate_speed) + app->player.dir_y * cos(-app->player.rotate_speed);
	old_plane_x = app->player.plane_x;
	app->player.plane_x = app->player.plane_x * cos(-app->player.rotate_speed) - app->player.plane_y * sin(-app->player.rotate_speed);
	app->player.plane_y = old_plane_x * sin(-app->player.rotate_speed) + app->player.plane_y * cos(-app->player.rotate_speed);
}

void	rotate_right(t_app *app)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(app->player.rotate_speed) - app->player.dir_y * sin(app->player.rotate_speed);
	app->player.dir_y = old_dir_x * sin(app->player.rotate_speed) + app->player.dir_y * cos(app->player.rotate_speed);
	old_plane_x = app->player.plane_x;
	app->player.plane_x = app->player.plane_x * cos(app->player.rotate_speed) - app->player.plane_y * sin(app->player.rotate_speed);
	app->player.plane_y = old_plane_x * sin(app->player.rotate_speed) + app->player.plane_y * cos(app->player.rotate_speed);
}
