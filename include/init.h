#ifndef INIT_H
# define INIT_H

# include "cub3d.h"

// Initializes the game, loading the map and setting up all components.
int	init_game(t_app *app, char *map_path);

// Initializes the game window.
int	init_window(t_app *app);

// Loads and initializes textures.
int	init_textures(t_app *app);

// Initializes the player position and direction.
int	init_player(t_app *app);

// Loads and initializes the map data.
int	init_map(t_app *app);

#endif
