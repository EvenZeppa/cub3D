/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:58:12 by vbonnard          #+#    #+#             */
/*   Updated: 2025/05/21 11:58:12 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
