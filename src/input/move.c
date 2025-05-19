#include "cub3d.h"

/* Fonction qui avance le joueur */
void	move_forward(t_app *app)
{
	double	next_x;
	double	next_y;
	int		direction_x;
	int		direction_y;

	next_x = app->player.x + app->player.dir_x * app->player.move_speed;
	next_y = app->player.y + app->player.dir_y * app->player.move_speed;
	direction_x = 0;
	direction_y = 0;
	if (app->player.dir_x > 0)
		direction_x = 1;
	else if (app->player.dir_x < 0)
		direction_x = -1;
	if (app->player.dir_y > 0)
		direction_y = 1;
	else if (app->player.dir_y < 0)
		direction_y = -1;
	if (app->file_data.map[(int)(app->player.y)]
			[(int)(next_x + COLLISION_MARGIN * direction_x)] != '1')
		app->player.x = next_x;
	if (app->file_data.map[(int)(next_y + COLLISION_MARGIN * direction_y)]
		[(int)(app->player.x)] != '1')
		app->player.y = next_y;
}

/* Fonction qui recule le joueur */
void	move_backward(t_app *app)
{
	double	next_x;
	double	next_y;
	int		direction_x;
	int		direction_y;

	next_x = app->player.x - app->player.dir_x * app->player.move_speed;
	next_y = app->player.y - app->player.dir_y * app->player.move_speed;
	direction_x = 0;
	direction_y = 0;
	if (app->player.dir_x > 0)
		direction_x = 1;
	else if (app->player.dir_x < 0)
		direction_x = -1;
	if (app->player.dir_y > 0)
		direction_y = 1;
	else if (app->player.dir_y < 0)
		direction_y = -1;
	if (app->file_data.map[(int)(app->player.y)]
			[(int)(next_x - COLLISION_MARGIN * direction_x)] != '1')
		app->player.x = next_x;
	if (app->file_data.map[(int)(next_y - COLLISION_MARGIN * direction_y)]
		[(int)(app->player.x)] != '1')
		app->player.y = next_y;
}

/* Fonction qui déplace le joueur à droite */
void	move_right(t_app *app)
{
	double	next_x;
	double	next_y;
	int		direction_x;
	int		direction_y;

	next_x = app->player.x - app->player.dir_y * app->player.move_speed;
	next_y = app->player.y + app->player.dir_x * app->player.move_speed;
	direction_x = 0;
	direction_y = 0;
	if (app->player.dir_y > 0)
		direction_x = 1;
	else if (app->player.dir_y < 0)
		direction_x = -1;
	if (app->player.dir_x > 0)
		direction_y = 1;
	else if (app->player.dir_x < 0)
		direction_y = -1;
	if (app->file_data.map[(int)(app->player.y)]
			[(int)(next_x - COLLISION_MARGIN * direction_x)] != '1')
		app->player.x = next_x;
	if (app->file_data.map[(int)(next_y + COLLISION_MARGIN * direction_y)]
			[(int)(app->player.x)] != '1')
		app->player.y = next_y;
}

/* Fonction qui déplace le joueur à gauche */
void	move_left(t_app *app)
{
	double	next_x;
	double	next_y;
	int		direction_x;
	int		direction_y;

	next_x = app->player.x + app->player.dir_y * app->player.move_speed;
	next_y = app->player.y - app->player.dir_x * app->player.move_speed;
	direction_x = 0;
	direction_y = 0;
	if (app->player.dir_y > 0)
		direction_x = 1;
	else if (app->player.dir_y < 0)
		direction_x = -1;
	if (app->player.dir_x > 0)
		direction_y = 1;
	else if (app->player.dir_x < 0)
		direction_y = -1;
	if (app->file_data.map[(int)(app->player.y)]
			[(int)(next_x + COLLISION_MARGIN * direction_x)] != '1')
		app->player.x = next_x;
	if (app->file_data.map[(int)(next_y - COLLISION_MARGIN * direction_y)]
			[(int)(app->player.x)] != '1')
		app->player.y = next_y;
}

// void	move_forward(t_app *app)
// {
// 	app->player.x += app->player.dir_x * app->player.move_speed;
// 	app->player.y += app->player.dir_y * app->player.move_speed;
// }

// void	move_backward(t_app *app)
// {
// 	app->player.x -= app->player.dir_x * app->player.move_speed;
// 	app->player.y -= app->player.dir_y * app->player.move_speed;
// }

// void	move_right(t_app *app)
// {
// 	app->player.x -= app->player.dir_y * app->player.move_speed;
// 	app->player.y += app->player.dir_x * app->player.move_speed;
// }

// void	move_left(t_app *app)
// {
// 	app->player.x += app->player.dir_y * app->player.move_speed;
// 	app->player.y -= app->player.dir_x * app->player.move_speed;
// }
