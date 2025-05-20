#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

// Parses the configuration file and initializes the app structure.
int		parse_file(t_app *app, const char *filename);

// Parses color information from the configuration.
int		parse_colors(t_app *app);

// Parses texture paths from the configuration.
int		parse_textures(t_app *app);

// Parses the map layout from the configuration.
int		parse_map(t_app *app);

// Checks the validity of the parsed map.
int		check_map(t_app *app);

// Returns 1 if the character is a valid player character, 0 otherwise.
int		is_player_char(char c);

// Returns 1 if the character is valid in the map, 0 otherwise.
int		is_valid_map_char(char c);

// Returns 1 if the line represents a map line, 0 otherwise.
int		is_map_line(const char *line);

// Calculates the dimensions (columns and rows) of the map.
void	calculate_map_dimensions(char **map, t_cols_rows *cols_rows);

#endif
