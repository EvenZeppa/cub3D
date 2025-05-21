#include "cub3d.h"

static int	load_texture(t_app *app, t_image *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(app->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (1);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->size_line, &tex->endian);
	if (!tex->addr)
		return (1);
	return (0);
}

/* Fonction globale qui va charger les textures N W E et S */
int	init_textures(t_app *app)
{
	if (load_texture(app, &app->textures[0], app->file_data.texture_north))
		return (1);
	if (load_texture(app, &app->textures[1], app->file_data.texture_south))
		return (1);
	if (load_texture(app, &app->textures[2], app->file_data.texture_east))
		return (1);
	if (load_texture(app, &app->textures[3], app->file_data.texture_west))
		return (1);
	return (0);
}
