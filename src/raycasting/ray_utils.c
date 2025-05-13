// #include "cub3d.h"

// int perform_dda(t_app *app, double dx, double dy, double *hit_x, double *hit_y)
// {
// 	double x = app->player.x;
// 	double y = app->player.y;
// 	int step = 0;

// 	while (step < 64)
// 	{
// 		int mx = (int)x;
// 		int my = (int)y;

// 		if (mx < 0 || mx >= MAP_WIDTH || my < 0 || my >= MAP_HEIGHT)
// 			break;

// 		if (app->file_data.map[my][mx] == 1)
// 		{
// 			*hit_x = x;
// 			*hit_y = y;
// 			return (0); // succès
// 		}
// 		x += dx * 0.05;
// 		y += dy * 0.05;
// 		step++;
// 	}
// 	*hit_x = x;
// 	*hit_y = y;
// 	return (0); // même si pas touché, on retourne un point max
// }
