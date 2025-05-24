#include "cub3d.h"

int is_duplicate_textures(char **file_data, int lines_count)
{
	int		i;
	int		count;
	char	*line;

	i = 0;
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
	}
	if (count > 4)
		return (1);
	return (0);
}

int	parse_textures(t_app *app)
{
	int		i;
	char	*line;

	if (is_duplicate_textures(app->file_data.file_data, app->file_data.lines_count))
		exit_error(app, "Duplicate texture definitions");
	i = 0;
	while (i < app->file_data.lines_count)
	{
		line = get_formatted_line(app->file_data.file_data[i]);
		
		i++;
	}
	return (0);
}
