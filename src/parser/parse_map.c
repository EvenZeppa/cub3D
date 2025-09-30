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
	if (copy_map_lines(app, start, map_lines))
		return (1);
	app->file_data.cols = ft_strlen(app->file_data.file_data[start]);
	if (app->file_data.cols == 0)
		return (1);
	return (0);
}
