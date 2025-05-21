#include "cub3d.h"

/* Fonction qui va uniquement initialiser l'ouverture du fichier */
static int	initialize_file_data(t_app *app, const char *filename, int *fd)
{
	int	capacity;

	capacity = 16;
	app->file_data.file_data = malloc(sizeof(char *) * capacity);
	if (!app->file_data.file_data)
		return (-1);
	*fd = open(filename, O_RDONLY);
	if (*fd < 0)
		return (free(app->file_data.file_data), -1);
	return (capacity);
}

/* Fonction qui va lire les lignes du fichier pour les stocker dans app*/
static int	read_file_lines(t_app *app, int fd, int capacity)
{
	char	*line;
	char	**temp;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i >= capacity)
		{
			capacity *= 2;
			temp = realloc(app->file_data.file_data, sizeof(char *) * capacity);
			if (!temp)
				return (close(fd), 1);
			app->file_data.file_data = temp;
		}
		app->file_data.file_data[i++] = line;
		line = get_next_line(fd);
	}
	app->file_data.file_data[i] = NULL;
	app->file_data.lines_count = i;
	if (i == 0)
		return (close(fd), 1);
	return (0);
}

/* Stocke les valeurs du fichier dans app->file_data.file_data.
	Retourne une erreur si probleme lors de l'ouverture du fichier
	ou de la lecture */
static int	prepare_file_data(t_app *app, const char *filename)
{
	int	fd;
	int	capacity;

	capacity = initialize_file_data(app, filename, &fd);
	if (capacity < 0)
		return (-1);
	if (read_file_lines(app, fd, capacity) < 0)
		return (-1);
	close(fd);
	return (0);
}

/* Fonction qui free les donnees stockees du fichier */
static void	free_file_data(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->file_data.lines_count)
	{
		free(app->file_data.file_data[i]);
		i++;
	}
	free(app->file_data.file_data);
	app->file_data.file_data = NULL;
	app->file_data.lines_count = 0;
}

/* Fonction principale du parsing */
int	parse_file(t_app *app, const char *filename)
{
	if (prepare_file_data(app, filename))
		exit_error(app, "prepare file data");
	if (app->file_data.lines_count == 0)
		exit_error(app, "file is empty");
	if (parse_textures(app))
		exit_error(app, "parsing textures");
	if (parse_colors(app))
		exit_error(app, "parsing colors");
	if (parse_map(app))
		exit_error(app, "parsing map");
	free_file_data(app);
	for (int i = 0; i < app->file_data.lines_count; i++)
		printf("[%d] %s", i, app->file_data.file_data[i]);
	return (0);
}
