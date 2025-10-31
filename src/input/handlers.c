/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:58:12 by vbonnard          #+#    #+#             */
/*   Updated: 2025/05/21 11:58:12 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_app *app)
{
	int		delta_x;
	double	angle;
	double	old_dir_x;

	(void)y;
	if (!app->mouse_initialized)
	{
		app->prev_mouse_x = x;
		app->mouse_initialized = 1;
		return (0);
	}
	if (abs(x - app->prev_mouse_x) > WIN_WIDTH - 10)
		return (app->prev_mouse_x = x, 0);
	delta_x = x - app->prev_mouse_x;
	app->prev_mouse_x = x;
	if (delta_x == 0)
		return (0);
	angle = delta_x * app->mouse_sensitivity;
	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(angle)
		- app->player.dir_y * sin(angle);
	app->player.dir_y = old_dir_x * sin(angle)
		+ app->player.dir_y * cos(angle);
	return (0);
}

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
