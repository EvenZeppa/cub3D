#include "cub3d.h"

/* Sort du programme en y affichant une erreur */
int	exit_error(t_app *app, char *message)
{
	(void) message;
	printf("Error\n");
	free_game(app);
	exit(1);
}
