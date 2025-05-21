#include "cub3d.h"

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
	if (!split || !split[0] || !split[1] || !split[2])
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

int	parse_colors(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->file_data.lines_count)
	{
		if (ft_strnstr(app->file_data.file_data[i], "C ", 2))
			app->file_data.ceiling = parse_rgb(app->file_data.file_data[i] + 2);
		else if (ft_strnstr(app->file_data.file_data[i], "F ", 2))
			app->file_data.floor = parse_rgb(app->file_data.file_data[i] + 2);
		i++;
	}
	return (0);
}
