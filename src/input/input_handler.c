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
	return (0);
}
