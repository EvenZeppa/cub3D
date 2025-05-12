#include "cub3d.h"

static int	load_texture(t_app *app, t_texture *tex, char *path)
{
	int		bpp;
	int		size_line;
	int		endian;

	tex->img = mlx_xpm_file_to_image(app->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->pixels = (int *)mlx_get_data_addr(tex->img, &bpp, &size_line, &endian);
	if (!tex->pixels)
		return (1);
	return (0);
}

int	init_textures(t_app *app)
{
	if (load_texture(app, &app->texture[0], app->file_data.texture_north))
		exit_error(app, "load tex north");
	if (load_texture(app, &app->texture[1], app->file_data.texture_south))
		exit_error(app, "load tex south");
	if (load_texture(app, &app->texture[2], app->file_data.texture_east))
		exit_error(app, "load tex east");
	if (load_texture(app, &app->texture[3], app->file_data.texture_west))
		exit_error(app, "load tex west");
	return (0);
}
