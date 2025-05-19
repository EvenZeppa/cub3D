#include "cub3d.h"

/*	Fonction qui va modifier la couleur de chaque pixel
	de la fenêtre en noir pour la refresh */
void	clear_frame(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(&app->frame, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

// void	draw_background(t_app *app);

/* Fonction principale pour rendre la fenetre et l'afficher */
// int	render_frame(t_app *app)
// {
// 	// printf("render frame\n");
// 	// // Print all data from map and player for debug
// 	// printf("Player X: %f, Y: %f\n", app->player.x, app->player.y);
// 	// printf("Player dir X: %f, Y: %f\n", app->player.dir_x, app->player.dir_y);
// 	// printf("Player angle: %f\n", app->player.angle);
// 	// printf("Player move speed: %f\n", app->player.move_speed);
// 	// printf("Player rotate speed: %f\n", app->player.rotate_speed);
// 	// printf("Map:\n");
// 	// for (int i = 0; i < app->file_data.rows; i++)
// 	// {
// 	// 	for (int j = 0; j < app->file_data.cols; j++)
// 	// 		printf("%c", app->file_data.map[i][j]);
// 	// 	printf("\n");
// 	// }
// 	// printf("Nunber of cols: %d\n", app->file_data.cols);
// 	// printf("Nunber of rows: %d\n", app->file_data.rows);
// 	clear_frame(app);
// 	// if (draw_minimap(app))
// 	// 	return (1);
// 	// if (cast_all_rays(app))
// 	// 	return (1);
// 	render_scene(app);
// 	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
// 	return (0);
// }

int	get_texture_pixel(t_image *tex, int x, int y)
{
	if (!tex || !tex->addr)
		return (0xFFFFFF); // blanc par défaut si texture invalide

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0xFF00FF); // rose fluo = pixel hors limite (debug)

	char	*pixel_line = tex->addr + y * tex->size_line;
	int		*pixels = (int *)pixel_line;

	return pixels[x];
}


void render_frame(t_app *app)
{
	// créer une image vide ou utiliser une image déjà créée
	app->frame.img = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	app->frame.addr = mlx_get_data_addr(app->frame.img, &app->frame.bpp, &app->frame.size_line, &app->frame.endian);

	render_scene(app); // dessine dans app->frame.addr
	// dessine la minimap
	// draw_minimap(app);

	// mlx_put_image_to_window(app->mlx, app->win, app->textures[0].img, 0, 0);
	// mlx_put_image_to_window(app->mlx, app->win, app->textures[1].img, 64, 0);
	// mlx_put_image_to_window(app->mlx, app->win, app->textures[2].img, 128, 0);
	// mlx_put_image_to_window(app->mlx, app->win, app->textures[3].img, 192, 0);

	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	mlx_destroy_image(app->mlx, app->frame.img); // optionnel si recréée à chaque frame
}


t_image *choose_wall_texture(t_app *app, int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0) // vertical wall
		return (ray_dir_x < 0) ? &app->textures[3] : &app->textures[2]; // W or E
	else // horizontal wall
		return (ray_dir_y < 0) ? &app->textures[0] : &app->textures[1]; // N or S
}


void	render_scene(t_app *app)
{
	// Crée l'image si elle n'existe pas encore
	if (!app->frame.img)
	{
		app->frame.img = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
		app->frame.addr = mlx_get_data_addr(app->frame.img,
											&app->frame.bpp,
											&app->frame.size_line,
											&app->frame.endian);
	}

	double base_angle = get_player_angle(app);
	double start_angle = base_angle - (FOV / 2);

	for (int i = 0; i < WIN_WIDTH; i++)
	{
		double ray_angle = start_angle + ((double)i / NUM_RAYS) * FOV;
		double ray_dir_x = cos(ray_angle);
		double ray_dir_y = sin(ray_angle);
		double hit_x, hit_y;
		int side;

		double dist = perform_dda_3d(app->file_data.map,
									 get_map_width(app->file_data.map),
									 get_map_height(app->file_data.map),
									 app->player.x,
									 app->player.y,
									 ray_dir_x, ray_dir_y,
									 &side, &hit_x, &hit_y);

		if (dist < 0)
			continue;

		double corrected_dist = dist * cos(ray_angle - base_angle);
		if (corrected_dist <= 0.0001)
			corrected_dist = 0.0001;

		int wall_height = (int)(WIN_HEIGHT / corrected_dist);
		// if (wall_height > WIN_HEIGHT)
		// 	wall_height = WIN_HEIGHT;
		int draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
		int draw_end = wall_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0) draw_start = 0;
		
		if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

		int screen_x = i * (WIN_WIDTH / NUM_RAYS);
		// int screen_x = i;

		for (int y = 0; y < WIN_HEIGHT; y++)
		{
			if (y < draw_start)
				my_mlx_pixel_put(&app->frame, screen_x, y,
					(app->file_data.ceiling.red << 16) |
					(app->file_data.ceiling.green << 8) |
					app->file_data.ceiling.blue);
			else if (y >= draw_start && y <= draw_end)
			{
				t_image *tex = choose_wall_texture(app, side, ray_dir_x, ray_dir_y);
				if (!tex || !tex->addr)
					continue;

				double wall_x = (side == 0) ? hit_y : hit_x;
				wall_x -= floor(wall_x);

				// clamp wall_x entre 0 et 1 (par sécurité)
				if (wall_x < 0.0) wall_x = 0.0;
				if (wall_x > 1.0) wall_x = 1.0;

				int tex_x = (int)(wall_x * tex->width);
				if (tex_x < 0) tex_x = 0;
				if (tex_x >= tex->width) tex_x = tex->width - 1;

				if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
					tex_x = tex->width - tex_x - 1;

				int d = y * 256 - WIN_HEIGHT * 128 + wall_height * 128;
				int tex_y = ((d * tex->height) / wall_height) / 256;
				if (tex_y < 0) tex_y = 0;
				if (tex_y >= tex->height) tex_y = tex->height - 1;
				// printf("tex_x=%d tex_y=%d\n", tex_x, tex_y);
				// int color = tex->addr[tex_y * tex->width + tex_x];
				int color = get_texture_pixel(tex, tex_x, tex_y);
				my_mlx_pixel_put(&app->frame, screen_x, y, color);
			}
			else
				my_mlx_pixel_put(&app->frame, screen_x, y,
					(app->file_data.floor.red << 16) |
					(app->file_data.floor.green << 8) |
					app->file_data.floor.blue);
		}
	}
	// Affiche l’image complète à l’écran en une seule fois
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}


