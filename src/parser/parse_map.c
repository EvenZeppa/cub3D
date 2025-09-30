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

// Fonction pour copier un char** terminé par NULL
char	**copy_string_array(char **src)
{
	size_t	count;
	size_t	i;
	size_t	j;
	char	**dest;

	count = 0;
	while (src[count] != NULL)
		count++;
	dest = malloc((count + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < count)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
		{
			j = -1;
			while (++j < i)
				free(dest[j]);
			return (free(dest), NULL);
		}
	}
	return (dest[count] = NULL, dest);
}

static int	copy_map_lines(t_app *app, int start, int map_lines)
{
	(void) map_lines;
	if (!(app->file_data.file_data + start))
		app->file_data.map = NULL;
	else
		app->file_data.map
			= copy_string_array(app->file_data.file_data + start);
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
