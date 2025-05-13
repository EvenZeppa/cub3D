#include "cub3d.h"

int	key_press(int keycode, t_app *app)
{
	if (keycode == KEY_W)
		move_forward(app);
	else if (keycode == KEY_S)
		move_backward(app);
	else if (keycode == KEY_A)
		move_left(app);
	else if (keycode == KEY_D)
		move_right(app);
	else if (keycode == KEY_LEFT)
		rotate_left(app);
	else if (keycode == KEY_RIGHT)
		rotate_right(app);
	else if (keycode == KEY_ESC)
		free_game(app);
	printf("Player new data\n");
	printf("X: %f\n", app->player.x);
	printf("Y: %f\n", app->player.y);
	printf("Dir X: %f\n", app->player.dir_x);
	printf("Dir Y: %f\n", app->player.dir_y);
	printf("Plane X: %f\n", app->player.plane_x);
	printf("Plane Y: %f\n", app->player.plane_y);
	printf("Move speed: %f\n", app->player.move_speed);
	printf("Rotate speed: %f\n", app->player.rotate_speed);
	printf("Keycode: %d\n", keycode);
	return (0);
}
