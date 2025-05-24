#include "cub3d.h"

int	is_dup_textures(char **file_data, int lines_count)
{
	int		i;
	int		count;
	char	*line;

	i = 0;
	count = 0;
	while (i < lines_count)
	{
		line = get_formatted_line(file_data[i]);
		if (strncmp(line, "NO ", 3) == 0)
			count++;
		else if (strncmp(line, "SO ", 3) == 0)
			count++;
		else if (strncmp(line, "EA ", 3) == 0)
			count++;
		else if (strncmp(line, "WE ", 3) == 0)
			count++;
		free(line);
		i++;
	}
	if (count > 4)
		return (1);
	return (0);
}

int	parse_textures(t_app *app)
{
	int		i;
	char	*line;

	if (is_dup_textures(app->file_data.file_data, app->file_data.lines_count))
		return (1);
	i = 0;
	while (i < find_map_start(app))
	{
		line = get_formatted_line(app->file_data.file_data[i]);
		if (ft_strnstr(line, "NO ", 3))
			app->file_data.texture_north = ft_strldup(line + 3,
					ft_strlen(line) - 2);
		else if (ft_strnstr(line, "SO ", 3))
			app->file_data.texture_south = ft_strldup(line + 3,
					ft_strlen(line) - 2);
		else if (ft_strnstr(line, "WE ", 3))
			app->file_data.texture_west = ft_strldup(line + 3,
					ft_strlen(line) - 2);
		else if (ft_strnstr(line, "EA ", 3))
			app->file_data.texture_east = ft_strldup(line + 3,
					ft_strlen(line) - 2);
		free(line);
		i++;
	}
	return (0);
}
