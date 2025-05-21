#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

// Duplicates a string up to a given size.
char	*ft_strldup(const char *s, size_t size);

// Prints an error message and exits the game.
int		exit_error(t_app *app, char *message);

// Frees all allocated game resources.
int		free_game(t_app *app);

// Returns the width of the map.
int		get_map_width(char **map);

// Returns the height of the map.
int		get_map_height(char **map);

// Calculates and returns the player's angle.
double	get_player_angle(t_app *app);

// Sets a pixel in an image to a given color.
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

#endif
