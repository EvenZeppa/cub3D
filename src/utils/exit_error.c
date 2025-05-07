#include "cub3d.h"

int	exit_error(t_app *app, char *message)
{
	printf("Error : %s", message);
	free_game(app);
	exit(1);
}
