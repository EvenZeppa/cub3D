#include "cub3d.h"

int	init_player(t_app *app)
{
	int	x;
	int	y;

	x = 0;
	while (app->file_data.map[x] != 0)
	{
		y = 0;
		while (app->file_data.map[x][y] != 0)
		{
			app->player.x = x + 0.5;
			app->player.y = y + 0.5;
			if (app->file_data.map[x][y] == 'N')
				return (app->player.dir_x = 1, app->player.dir_y = 0, 0);
			if (app->file_data.map[x][y] == 'S')
				return (app->player.dir_x = -1, app->player.dir_y = 0, 0);
			if (app->file_data.map[x][y] == 'E')
				return (app->player.dir_x = 0, app->player.dir_y = 1, 0);
			if (app->file_data.map[x][y] == 'W')
				return (app->player.dir_x = 0, app->player.dir_y = -1, 0);
			y++;
		}
		x++;
	}
	return (1);
}
