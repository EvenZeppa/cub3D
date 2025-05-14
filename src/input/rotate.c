#include "cub3d.h"

/* Fonction pour faire les rotations a droite */
void	rotate_right(t_app *app)
{
	double	old_dir_x;
	double	angle;

	angle = app->player.rotate_speed;
	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(angle)
		- app->player.dir_y * sin(angle);
	app->player.dir_y = old_dir_x * sin(angle)
		+ app->player.dir_y * cos(angle);
}

/* Fonction pour faire les rotations a gauche */
void	rotate_left(t_app *app)
{
	double	old_dir_x;
	double	angle;

	angle = -app->player.rotate_speed;
	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(angle)
		- app->player.dir_y * sin(angle);
	app->player.dir_y = old_dir_x * sin(angle)
		+ app->player.dir_y * cos(angle);
}
