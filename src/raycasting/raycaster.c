#include "cub3d.h"

// int cast_ray(t_app *app)
// {
// 	double angle = get_player_angle(app);
// 	double dx = cos(angle);
// 	double dy = sin(angle);
// 	double hit_x, hit_y;

// 	if (perform_dda(app, dx, dy, &hit_x, &hit_y))
// 		return (1);

// 	double tile = get_minimap_tile_size(app); // à calculer comme dans draw_minimap()

// 	if (draw_ray(app,
// 			app->player.x * tile,
// 			app->player.y * tile,
// 			hit_x * tile,
// 			hit_y * tile,
// 			0xFF0000))
// 		return (1);
// 	return (0);
// }

// int cast_all_rays(t_app *app)
// {
// 	double player_angle = get_player_angle(app);
// 	double tile = get_minimap_tile_size(app);
// 	double angle_start = player_angle - (FOV / 2.0);
// 	double angle_step = FOV / NUM_RAYS;

// 	for (int i = 0; i < NUM_RAYS; i++)
// 	{
// 		double ray_angle = angle_start + i * angle_step;
// 		double ray_dir_x = cos(ray_angle);
// 		double ray_dir_y = sin(ray_angle);
// 		double hit_x, hit_y;

// 		if (perform_dda(app, ray_dir_x, ray_dir_y, &hit_x, &hit_y) == 0)
// 		{
// 			if (draw_ray(app,
// 					app->player.x * tile,
// 					app->player.y * tile,
// 					hit_x * tile,
// 					hit_y * tile,
// 					0xFF0000))
// 				return (1);
// 		}
// 	}
// 	return (0);
// }

// int	cast_all_rays(t_app *app)
// {
// 	int		r,mx,my,mp,dof;
// 	double	rx,ry,ra,xo,yo;

// 	ra = get_player_angle(app);
// 	for (r=0;r<1;r++)
// 	{
// 		dof = 0;
// 		double aTan = -1 / tan(ra);
// 		if (ra > M_PI) // looking up
// 		{
// 			ry = (((int)app->player.y >> 6) << 6) - 0.0001;
// 			rx = (app->player.y - ry) * aTan + app->player.x;
// 			yo = -64;
// 			xo = -yo * aTan;
// 		}
// 		if (ra < M_PI) // looking down
// 		{
// 			ry = (((int)app->player.y >> 6) << 6) + 64;
// 			rx = (app->player.y - ry) * aTan + app->player.x;
// 			yo = 64;
// 			xo = -yo * aTan;
// 		}
// 		if (ra == 0 || ra == M_PI) // looking straight left or right
// 		{
// 			rx = app->player.x;
// 			ry = app->player.y;
// 			dof = 8;
// 		}
// 		while (dof < 8)
// 		{
// 			mx = (int)(rx) >> 6;
// 			my = (int)(ry) >> 6;
// 			mp = my * app->file_data.cols + mx;
// 			if (mp < app->file_data.cols * app->file_data.rows && app->file_data.map[my][mx] == '1')
// 			{
// 				dof = 8;
// 				printf("ray %d: %d %d %d %d\n", r, mx, my, rx, ry);
// 				break;
// 			}
// 			else
// 			{
// 				rx += xo;
// 				ry += yo;
// 				dof++;
// 			}
// 		}
// 		draw_ray(app,
// 			app->player.x * get_minimap_tile_size(app),
// 			app->player.y * get_minimap_tile_size(app),
// 			rx * get_minimap_tile_size(app),
// 			ry * get_minimap_tile_size(app),
// 			0xFF0000);
// 	}
// 	return (0);
// }


