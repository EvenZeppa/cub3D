#include "cub3d.h"

/**
 * @brief Charge une texture à partir d'un fichier XPM et initialise la structure t_image.
 *
 * Cette fonction utilise la bibliothèque MiniLibX pour charger une image XPM depuis le chemin spécifié,
 * puis récupère l'adresse des données de l'image. Si le chargement échoue à n'importe quelle étape,
 * la fonction retourne 1 pour indiquer une erreur, sinon 0 en cas de succès.
 *
 * @param app Pointeur vers la structure principale de l'application contenant le contexte MLX.
 * @param tex Pointeur vers la structure t_image à initialiser avec l'image chargée.
 * @param path Chemin du fichier XPM à charger.
 * @return int 0 si la texture est chargée avec succès, 1 en cas d'échec.
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
