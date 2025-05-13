#include "cub3d.h"

t_rgb parse_rgb(char *line)
{
	t_rgb	rgb;
	char	**split;

	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free(split);
		exit_error(NULL, "Invalid RGB format");
	}
	rgb.red = ft_atoi(split[0]);
	rgb.green = ft_atoi(split[1]);
	rgb.blue = ft_atoi(split[2]);
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