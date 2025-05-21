#include "cub3d.h"

int	init_map(t_app *app)
{
	if (check_map(app))
		exit_error(app, "check map");
	return (0);
}
