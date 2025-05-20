#include "cub3d.h"

int	get_texture_pixel(t_image *tex, int x, int y)
{
	char	*pixel_line;
	int		*pixels;

	if (!tex || !tex->addr)
		return (0xFFFFFF);
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0xFF00FF);
	pixel_line = tex->addr + y * tex->size_line;
	pixels = (int *)pixel_line;
	return (pixels[x]);
}

void	render_frame(t_app *app)
{
	app->frame.img = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
	app->frame.addr = mlx_get_data_addr(app->frame.img,
			&app->frame.bpp, &app->frame.size_line, &app->frame.endian);
	render_scene(app);
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
	mlx_destroy_image(app->mlx, app->frame.img);
	app->frame.img = NULL;
}

t_image	*choose_wall_texture(t_app *app,
	int side, double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x < 0)
			return (&app->textures[3]);
		else if (ray_dir_x > 0)
			return (&app->textures[2]);
	}
	else
	{
		if (ray_dir_y < 0)
			return (&app->textures[0]);
		else if (ray_dir_y > 0)
			return (&app->textures[1]);
	}
	return (NULL);
}

void	render_scene(t_app *app)
{
	double	base_angle;
	int		i;
	t_ray	ray;

	if (!app->frame.img)
	{
		app->frame.img = mlx_new_image(app->mlx, WIN_WIDTH, WIN_HEIGHT);
		app->frame.addr = mlx_get_data_addr(app->frame.img,
				&app->frame.bpp, &app->frame.size_line, &app->frame.endian);
	}
	base_angle = get_player_angle(app);
	i = 0;
	while (i < NUM_RAYS)
	{
		compute_ray_info(app, &ray, i, base_angle);
		draw_column(app, &ray);
		i++;
	}
	mlx_put_image_to_window(app->mlx, app->win, app->frame.img, 0, 0);
}
