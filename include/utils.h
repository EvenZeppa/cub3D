#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

char	*ft_strldup(const char *s, size_t size);
int	exit_error(t_app *app, char *message);
int	free_game(t_app *app);
int	get_map_width(char **map);
int	get_map_height(char **map);
double get_player_angle(t_app *app);
double get_minimap_tile_size(t_app *app);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

#endif
