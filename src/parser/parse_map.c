#include "cub3d.h"
int	is_map_line(const char *line)
{
	while (*line)
	{
		if (*line == '1' || *line == '0' ||
			*line == 'N' || *line == 'S' ||
			*line == 'E' || *line == 'W' ||
			*line == ' ')
			return (1);
		else if (!isspace(*line)) // si ce n’est pas un caractère valide, on arrête
			return (0);
		line++;
	}
	return (0);
}

int	parse_map(t_app *app)
{
	int		start = -1;
	int		total_lines = app->file_data.lines_count;
	int		map_lines = 0;
	int		i;

	// Trouver l’indice du début de la map
	for (i = 0; i < total_lines; i++)
	{
		if (is_map_line(app->file_data.file_data[i]))
		{
			start = i;
			break;
		}
	}

	if (start == -1)
		return (-1); // map non trouvée

	map_lines = total_lines - start;
	app->file_data.map = malloc(sizeof(char *) * (map_lines + 1));
	if (!app->file_data.map)
		return (-1);

	for (i = 0; i < map_lines; i++)
	{
		app->file_data.map[i] = strdup(app->file_data.file_data[start + i]);
		if (!app->file_data.map[i])
			return (-1); // en pratique tu devrais libérer ce qui a déjà été alloué
	}
	app->file_data.map[map_lines] = NULL;

	return (0);
}