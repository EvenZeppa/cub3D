#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

int	exit_error(t_app *app, char *message);
int	free_game(t_app *app);
int	get_map_width(char **map);
int	get_map_height(char **map);


#endif
