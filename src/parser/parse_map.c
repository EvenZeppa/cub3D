#include "cub3d.h"

/* Fonction qui cherche et renvoie l'index du debut de la map dans le fichier */
static int	find_map_start(t_app *app)
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

/* Alloue la memoire pour stocker la map */
static int	allocate_map(t_app *app, int map_lines)
{
	app->file_data.map = malloc(sizeof(char *) * (map_lines + 1));
	if (!app->file_data.map)
		return (1);
	return (0);
}

/* Fonction qui va copier les lignes du fichier
	pour les stocker dans la structure app */
static int	copy_map_lines(t_app *app, int start, int map_lines)
{
	int	i;

	i = 0;
	while (i < map_lines)
	{
		app->file_data.map[i] = ft_strldup(app->file_data.file_data[start + i],
				ft_strlen(app->file_data.file_data[start + i]));
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

/* Fonction principale pour parser la map */
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
