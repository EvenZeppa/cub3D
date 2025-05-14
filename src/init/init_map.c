#include "cub3d.h"

/* Fonction d'initialisation de la map qui va checker les instructions valides */
int	init_map(t_app *app, char *map_path)
{
	if (check_map(app))
		exit_error(app, "check map");
	return (0);
}
