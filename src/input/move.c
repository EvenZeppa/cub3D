#include "cub3d.h"

void	move_forward(t_app *app)
{
	double next_x = app->player.x + app->player.dir_x * app->player.move_speed;
	double next_y = app->player.y + app->player.dir_y * app->player.move_speed;

	// Applique la marge dans la direction du mouvement
	if (app->file_data.map[(int)(app->player.y)][(int)(next_x + COLLISION_MARGIN * ((app->player.dir_x > 0) ? 1 : -1))] != '1')
		app->player.x = next_x;
	if (app->file_data.map[(int)(next_y + COLLISION_MARGIN * ((app->player.dir_y > 0) ? 1 : -1))][(int)(app->player.x)] != '1')
		app->player.y = next_y;
}

void	move_backward(t_app *app)
{
	double next_x = app->player.x - app->player.dir_x * app->player.move_speed;
	double next_y = app->player.y - app->player.dir_y * app->player.move_speed;

	if (app->file_data.map[(int)(app->player.y)][(int)(next_x - COLLISION_MARGIN * ((app->player.dir_x > 0) ? 1 : -1))] != '1')
		app->player.x = next_x;
	if (app->file_data.map[(int)(next_y - COLLISION_MARGIN * ((app->player.dir_y > 0) ? 1 : -1))][(int)(app->player.x)] != '1')
		app->player.y = next_y;
}

void	move_left(t_app *app)
{
	double next_x = app->player.x - app->player.dir_y * app->player.move_speed;
	double next_y = app->player.y + app->player.dir_x * app->player.move_speed;

	if (app->file_data.map[(int)(app->player.y)][(int)(next_x - COLLISION_MARGIN * ((app->player.dir_y > 0) ? 1 : -1))] != '1')
		app->player.x = next_x;
	if (app->file_data.map[(int)(next_y + COLLISION_MARGIN * ((app->player.dir_x > 0) ? 1 : -1))][(int)(app->player.x)] != '1')
		app->player.y = next_y;
}

void	move_right(t_app *app)
{
	double next_x = app->player.x + app->player.dir_y * app->player.move_speed;
	double next_y = app->player.y - app->player.dir_x * app->player.move_speed;

	if (app->file_data.map[(int)(app->player.y)][(int)(next_x + COLLISION_MARGIN * ((app->player.dir_y > 0) ? 1 : -1))] != '1')
		app->player.x = next_x;
	if (app->file_data.map[(int)(next_y - COLLISION_MARGIN * ((app->player.dir_x > 0) ? 1 : -1))][(int)(app->player.x)] != '1')
		app->player.y = next_y;
}
