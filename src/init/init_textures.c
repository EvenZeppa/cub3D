#include "cub3d.h"

/**
 * @brief Charge une texture XPM dans une image MiniLibX.
 *
 * Utilise `mlx_xpm_file_to_image()` pour charger une image depuis un
 * fichier XPM, puis récupère son adresse mémoire avec
 * `mlx_get_data_addr()` afin de pouvoir manipuler ses pixels.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param tex Pointeur vers la structure image à remplir.
 * @param path Chemin vers le fichier XPM.
 * @return 0 si la texture a été chargée avec succès, 1 sinon.
 */
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

int	init_textures(t_app *app)
{
	if (load_texture(app, &app->textures[0], app->file_data.texture_north))
		exit_error(app, "load tex north");
	if (load_texture(app, &app->textures[1], app->file_data.texture_south))
		exit_error(app, "load tex south");
	if (load_texture(app, &app->textures[2], app->file_data.texture_east))
		exit_error(app, "load tex east");
	if (load_texture(app, &app->textures[3], app->file_data.texture_west))
		exit_error(app, "load tex west");
	return (0);
}
