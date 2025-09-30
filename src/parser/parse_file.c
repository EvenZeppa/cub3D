#include "cub3d.h"

/**
 * @brief Initialise les données de fichier pour l'application.
 *
 * Alloue un tableau dynamique de chaînes pour stocker les lignes du
 * fichier et ouvre le fichier en lecture seule.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param filename Nom du fichier à ouvrir.
 * @param fd Pointeur vers un int pour stocker le descripteur de fichier.
 * @return Capacité initiale allouée ou -1 en cas d'erreur.
 */
static int	initialize_file_data(t_app *app,
	const char *filename, int *fd)
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

/**
 * @brief Lit les lignes du fichier et les stocke dans app->file_data.
 *
 * Utilise get_next_line() pour lire le fichier ligne par ligne. Si la
 * capacité initiale est dépassée, le tableau est réaloué dynamiquement.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param fd Descripteur de fichier ouvert.
 * @param capacity Capacité initiale du tableau.
 * @return 0 si tout se passe bien, -1 en cas d'erreur.
 */
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
			temp = ft_realloc(app->file_data.file_data,
					sizeof(char *) * (capacity / 2), sizeof(char *) * capacity);
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

/**
 * @brief Prépare les données du fichier avant le parsing.
 *
 * Initialise la structure `file_data`, ouvre le fichier et lit les lignes.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param filename Chemin du fichier à lire.
 * @return 0 si succès, -1 en cas d'échec.
 */
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
	return (0);
}
