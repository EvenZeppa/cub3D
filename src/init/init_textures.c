#include "cub3d.h"

/**
 * @file init_textures.c
 * @brief Functions to initialize and load textures for the cub3D project.
 *
 * This file contains utility functions to check file suffixes and to load
 * XPM textures into MiniLibX images, as well as the main texture
 * initialization routine.
 */
int	ft_str_ends_with(const char *str, const char *suffix)
{
	size_t	str_len;
	size_t	suffix_len;

	if (!str || !suffix)
		return (0);
	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (suffix_len > str_len)
		return (0);
	return (ft_strcmp(str + str_len - suffix_len, suffix) == 0);
}

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
	if (!path)
		exit_error(app, "Texture path is NULL");
	if (!ft_str_ends_with(path, ".xpm"))
		exit_error(app, "Invalid texture file format");
	tex->img = mlx_xpm_file_to_image(app->mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		exit_error(app, "Failed to load texture image");
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->size_line, &tex->endian);
	if (!tex->addr)
		exit_error(app, "Failed to get texture data address");
	return (0);
}

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
