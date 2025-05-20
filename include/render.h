#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

// Renders a single frame of the game.
void	render_frame(t_app *app);

// Draws a vertical column for a given ray.
void	draw_column(t_app *app, t_ray *ray);

// Renders the entire scene (all columns).
void	render_scene(t_app *app);

// Retrieves the color value of a pixel from a texture.
int		get_texture_pixel(t_image *tex, int x, int y);

// Chooses the appropriate wall texture based on ray direction and side.
t_image	*choose_wall_texture(t_app *app,
			int side, double ray_dir_x, double ray_dir_y);

// Draw the minimap on the screen.
void draw_minimap(t_app *app);

#endif
