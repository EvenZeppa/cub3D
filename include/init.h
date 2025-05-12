#ifndef INIT_H
# define INIT_H

# include "cub3d.h"

int	init_game(t_app *app, char *map_path);
int	init_window(t_app *app);
int	init_textures(t_app *app);
int	init_player(t_app *app);
int	init_map(t_app *app, char *map_path);
#endif
