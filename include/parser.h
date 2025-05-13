#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

int	parse_file(t_app *app, const char *filename);
int	parse_colors(t_app *app);
int	parse_textures(t_app *app);
int	parse_map(t_app *app);
int	check_map(t_app *app);
int	is_player_char(char c);
int	is_valid_map_char(char c);
int	is_map_line(const char *line);

#endif
