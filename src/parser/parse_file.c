#include "cub3d.h"

/* Stocke les valeurs du fichier dans app->file_data.file_data.
	Retourne une erreur si probleme lors de l'ouverture du fichier
	ou de la lecture */
static int	prepare_file_data(t_app *app, const char *filename)
{
	int		fd;
	char	*line;
	char	**temp;
	int		capacity = 16;
	int		i = 0;

	app->file_data.file_data = malloc(sizeof(char *) * capacity);
	if (!app->file_data.file_data)
		return (-1);

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);

	while ((line = get_next_line(fd)))
	{
		if (i >= capacity)
		{
			capacity *= 2;
			temp = realloc(app->file_data.file_data, sizeof(char *) * capacity);
			if (!temp)
			{
				close(fd);
				return (-1);
			}
			app->file_data.file_data = temp;
		}
		app->file_data.file_data[i++] = line;
	}
	app->file_data.file_data[i] = NULL;
	app->file_data.lines_count = i;
	close(fd);
	return (0);
}

static void free_file_data(t_app *app)
{
	int	i;

	for (i = 0; i < app->file_data.lines_count; i++)
		free(app->file_data.file_data[i]);
	free(app->file_data.file_data);
	app->file_data.file_data = NULL;
	app->file_data.lines_count = 0;
}

int parse_file(t_app *app, const char *filename)
{
	if (prepare_file_data(app, filename))
		exit_error(app, "prepare file data");
	if (parse_textures(app))
		exit_error(app, "parsing textures");
	if (parse_colors(app))
		exit_error(app, "parsing colors");
	if (parse_map(app))
		exit_error(app, "parsing map");
	free_file_data(app);
	return (0);
}
