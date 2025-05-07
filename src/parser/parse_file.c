#include "cub3d.h"

int parse_file(const char *filename, t_app *app)
{
	if (prepare_file_data(app))
		exit_error(app, "prepare file data");
	if (parse_textures(app))
		exit_error(app, "parsing textures");
	if (parse_colors(app))
		exit_error(app, "parsing colors");
	if (parse_map(app))
		exit_error(app, "parsing map");
}
