#include "cub3d.h"

int	is_rgb_line_valid(char *line)
{
	int	i;
	int	comma_count;
	i = 0;
	comma_count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma_count++;
		else if (!isdigit(line[i]))
			return (0);
		i++;
	}
	return (comma_count == 2);
}

/**
 * @brief Parse une chaîne contenant une couleur RGB au format "R,G,B".
 *
 * Convertit une chaîne de caractères représentant une couleur RGB en une
 * structure t_rgb. La chaîne doit contenir trois entiers séparés par des
 * virgules (ex : "255,200,100"). En cas d'erreur de format, la fonction
 * appelle exit_error().
 *
 * @param line Chaîne contenant les trois composantes RGB.
 * @return Structure t_rgb contenant les valeurs rouge, vert et bleu.
 */
static t_rgb	parse_rgb(char *line)
{
	t_rgb	rgb;
	char	**split;
	char	**tmp;

	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2] || !is_rgb_line_valid(line))
	{
		free(split);
		exit_error(NULL, "Invalid RGB format");
	}
	rgb.red = ft_atoi(split[0]);
	rgb.green = ft_atoi(split[1]);
	rgb.blue = ft_atoi(split[2]);
	tmp = split;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(split);
	return (rgb);
}

/* Verifie la validite du rgb donne */
int	check_rgb(t_rgb rgb)
{
	if (rgb.red < 0 || rgb.red > 255 || rgb.green < 0
		|| rgb.green > 255 || rgb.blue < 0 || rgb.blue > 255)
		return (1);
	return (0);
}

/* Fonction pour parser le fichier afin de
	stocker les couleurs du plafond et du sol */
int	parse_colors(t_app *app)
{
	int		i;
	char	*line;

	i = 0;
	while (i < app->file_data.lines_count)
	{
		line = get_formatted_line(app->file_data.file_data[i]);
		if (ft_strnstr(line, "C ", 2))
			app->file_data.ceiling = parse_rgb(line + 2);
		else if (ft_strnstr(line, "F ", 2))
			app->file_data.floor = parse_rgb(line + 2);
		i++;
	}
	if (check_rgb(app->file_data.ceiling) || check_rgb(app->file_data.floor))
	{
		exit_error(app, "Error\n");
		return (1);
	}
	return (0);
}
