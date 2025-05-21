#include "cub3d.h"

/* Sort du programme en y affichant une erreur */
int	exit_error(t_app *app, char *message)
{
	printf("Error : %s\n", message);
	free_game(app);
	exit(1);
}
