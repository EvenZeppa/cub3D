#ifndef INPUT_H
# define INPUT_H

# include "cub3d.h"

// Handles key press events.
int		key_press(int keycode, t_app *app);

// Moves the player forward.
void	move_forward(t_app *app);

// Moves the player backward.
void	move_backward(t_app *app);

// Moves the player to the right (strafe).
void	move_right(t_app *app);

// Moves the player to the left (strafe).
void	move_left(t_app *app);

// Rotates the player to the left.
void	rotate_left(t_app *app);

// Rotates the player to the right.
void	rotate_right(t_app *app);

#endif