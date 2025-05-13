#include "cub3d.h"

int	get_map_width(char **map)
{
	int max = 0;
	int i = 0;
	while (map[i])
	{
		int len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	get_map_height(char **map)
{
	int i = 0;
	while (map[i])
		i++;
	return (i);
}

double get_player_angle(t_app *app)
{
	double angle;

	angle = atan2(app->player.dir_y, app->player.dir_x);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}
