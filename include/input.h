#ifndef INPUT_H
# define INPUT_H

# include "cub3d.h"

int		key_press(int keycode, t_app *app);
void	move_forward(t_app *app);
void	move_backward(t_app *app);
void	move_right(t_app *app);
void	move_left(t_app *app);
void	rotate_left(t_app *app);
void	rotate_right(t_app *app);

#endif