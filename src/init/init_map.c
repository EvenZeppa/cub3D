#include "cub3d.h"

int	init_map(t_app *app, char *map_path)
{
	if (parse_file(app, map_path))
		exit_error(app, "parse_file");
	if (check_map(app))
		exit_error(app, "check map");
}
