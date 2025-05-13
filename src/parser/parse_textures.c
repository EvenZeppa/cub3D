#include "cub3d.h"

int	parse_textures(t_app *app)
{
	int	i;

	i = 0;
	while (i < app->file_data.lines_count)
	{
		if (ft_strnstr(app->file_data.file_data[i], "NO ", 3))
			app->file_data.texture_north = ft_strldup(app->file_data.file_data[i] + 3, ft_strlen(app->file_data.file_data[i] + 3));
		else if (ft_strnstr(app->file_data.file_data[i], "SO ", 3))
			app->file_data.texture_south = ft_strldup(app->file_data.file_data[i] + 3, ft_strlen(app->file_data.file_data[i] + 3));
		else if (ft_strnstr(app->file_data.file_data[i], "WE ", 3))
			app->file_data.texture_west = ft_strldup(app->file_data.file_data[i] + 3, ft_strlen(app->file_data.file_data[i] + 3));
		else if (ft_strnstr(app->file_data.file_data[i], "EA ", 3))
			app->file_data.texture_east = ft_strldup(app->file_data.file_data[i] + 3, ft_strlen(app->file_data.file_data[i] + 3));
		i++;
	}
	return (0);
}
