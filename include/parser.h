#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

int	parse_file(t_app *app, const char *filename);
int	parse_colors(t_app *app);
int	parse_textures(t_app *app);
int	parse_map(t_app *app);

#endif
