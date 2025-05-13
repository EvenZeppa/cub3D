#include "cub3d.h"

void	move_forward(t_app *app)
{
	app->player.x += app->player.dir_x * app->player.move_speed;
	app->player.y += app->player.dir_y * app->player.move_speed;
}

void	move_backward(t_app *app)
{
	app->player.x -= app->player.dir_x * app->player.move_speed;
	app->player.y -= app->player.dir_y * app->player.move_speed;
}

void	move_right(t_app *app)
{
	app->player.x += app->player.dir_y * app->player.move_speed;
	app->player.y -= app->player.dir_x * app->player.move_speed;
}

void	move_left(t_app *app)
{
	app->player.x -= app->player.dir_y * app->player.move_speed;
	app->player.y += app->player.dir_x * app->player.move_speed;
}
