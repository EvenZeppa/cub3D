#include "cub3d.h"

int	parse_map(t_app *app)
{
	int		start = -1;
	int		total_lines = app->file_data.lines_count;
	int		map_lines = 0;
	int		i;

	for (i = 0; i < total_lines; i++)
	{
		if (is_map_line(app->file_data.file_data[i]))
		{
			start = i;
			break;
		}
	}

	if (start == -1)
		return (1);

	map_lines = total_lines - start;
	app->file_data.map = malloc(sizeof(char *) * (map_lines + 1));
	if (!app->file_data.map)
		return (1);

	for (i = 0; i < map_lines; i++)
	{
		app->file_data.map[i] = ft_strldup(app->file_data.file_data[start + i], ft_strlen(app->file_data.file_data[start + i]));
		if (!app->file_data.map[i])
		{
			while (i > 0)
				free(app->file_data.map[--i]);
			free(app->file_data.map);
			return (1);
		}
	}
	app->file_data.map[map_lines] = NULL;

	// print la map
	printf("Map: %d\n", map_lines);
	for (i = 0; i < map_lines; i++)
	{
		printf("%s\n", app->file_data.map[i]);
	}

	return (0);
}
