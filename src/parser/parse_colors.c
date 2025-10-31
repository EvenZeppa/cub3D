/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 16:43:35 by vbonnard          #+#    #+#             */
/*   Updated: 2025/10/31 14:21:57 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Vérifie que la ligne contient uniquement
des chiffres, espaces, et 2 virgules */
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
		else if (!ft_isdigit(line[i]) && line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (comma_count == 2);
}

/* Vérifie la validité des composantes RGB */
int	check_rgb(t_rgb rgb)
{
	if (rgb.red < 0 || rgb.red > 255
		|| rgb.green < 0 || rgb.green > 255
		|| rgb.blue < 0 || rgb.blue > 255)
		return (1);
	return (0);
}

/**
 * @brief Parse une chaîne contenant une couleur RGB au format "R,G,B".
 * 
 * @param line Chaîne contenant les trois composantes RGB.
 * @param rgb Pointeur vers la structure à remplir.
 * @return int 0 si succès, 1 si erreur.
 */
static int	parse_rgb(t_app *app, char *line, t_rgb *rgb)
{
	char	**split;

	if (!is_rgb_line_valid(line + 2))
	{
		free(line);
		exit_error(app, "Invalid RGB line format");
	}
	split = ft_split(line + 2, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free_split(split);
		free(line);
		exit_error(app, "Missing RGB components");
	}
	rgb->red = ft_atoi(split[0]);
	rgb->green = ft_atoi(split[1]);
	rgb->blue = ft_atoi(split[2]);
	free_split(split);
	if (check_rgb(*rgb))
	{
		free(line);
		exit_error(app, "RGB values out of range");
	}
	return (0);
}

static int	handle_color_line(t_app *app, char *line,
	t_file_data *data, int *count)
{
	if (ft_strnstr(line, "C ", 2))
	{
		if (parse_rgb(app, line, &data->ceiling))
			exit_error(app, "Invalid ceiling color format");
		(*count)++;
	}
	else if (ft_strnstr(line, "F ", 2))
	{
		if (parse_rgb(app, line, &data->floor))
			exit_error(app, "Invalid floor color format");
		(*count)++;
	}
	return (0);
}

int	parse_colors(t_app *app)
{
	int		i;
	char	*line;
	int		count;
	int		error;

	i = 0;
	count = 0;
	error = 0;
	while (i < find_map_start(app))
	{
		line = get_formatted_line(app->file_data.file_data[i]);
		if (!line)
			exit_error(app, "Memory allocation failed");
		if (handle_color_line(app, line, &app->file_data, &count))
			error = 1;
		free(line);
		i++;
	}
	if (count < 2)
		exit_error(app, "Missing color definitions");
	else if (count > 2)
		exit_error(app, "Too much color definitions");
	return (error);
}
