#include "cub3d.h"

/**
 * @brief Trouve l'index de la première ligne correspondant à la map.
 *
 * Parcourt les lignes du fichier de configuration pour trouver la
 * première ligne considérée comme appartenant à la carte.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @return Index de début de la map, ou -1 si aucune ligne valide n’est trouvée.
 */
int	find_map_start(t_app *app)
{
	int	total_lines;
	int	i;

	total_lines = app->file_data.lines_count;
	i = 0;
	while (i < total_lines)
	{
		if (is_map_line(app->file_data.file_data[i]))
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Alloue la mémoire pour stocker les lignes de la carte.
 *
 * Alloue un tableau de chaînes qui contiendra toutes les lignes
 * représentant la carte dans le fichier de configuration.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param map_lines Nombre de lignes de la carte à allouer.
 * @return 0 si succès, 1 en cas d'échec d’allocation.
 */
static int	allocate_map(t_app *app, int map_lines)
{
	app->file_data.map = malloc(sizeof(char *) * (map_lines + 1));
	if (!app->file_data.map)
		return (1);
	return (0);
}

/**
 * @brief Copie les lignes de la carte depuis les données du fichier.
 *
 * Duplique les lignes du fichier à partir d’un index donné pour
 * les stocker dans la structure `map`. En cas d’échec, libère
 * proprement la mémoire allouée.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param start Index de la première ligne de la carte dans file_data.
 * @param map_lines Nombre total de lignes à copier.
 * @return 0 si succès, 1 en cas d’erreur d’allocation.
 */
static int	copy_map_lines(t_app *app, int start, int map_lines)
{
	int	i;
	int	is_end;

	i = 0;
	while (i < map_lines)
	{
		if (i == map_lines - 1)
			is_end = 1;
		else
			is_end = 0;
		app->file_data.map[i] = ft_strldup(app->file_data.file_data[start + i],
			ft_strlen(app->file_data.file_data[start + i]) + is_end);
		if (!app->file_data.map[i])
		{
			while (i > 0)
				free(app->file_data.map[--i]);
			free(app->file_data.map);
			return (1);
		}
		i++;
	}
	app->file_data.map[map_lines] = NULL;
	return (0);
}

int	parse_map(t_app *app)
{
	int	start;
	int	map_lines;
	
	start = find_map_start(app);
	if (start == -1)
		return (1);
	map_lines = app->file_data.lines_count - start;
	app->file_data.rows = map_lines;
	if (allocate_map(app, map_lines))
		return (1);
	if (copy_map_lines(app, start, map_lines))
		return (1);
	app->file_data.cols = ft_strlen(app->file_data.file_data[start]);
	if (app->file_data.cols == 0)
		return (1);
	return (0);
}
