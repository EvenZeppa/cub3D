#include "cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || is_player_char(c) || c == ' ');
}

int	is_map_line(const char *line)
{
	int	i;

	if (line[0] == '\n')
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!is_valid_map_char(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	calculate_map_dimensions(char **map, t_cols_rows *cols_rows)
{
	int	rows;
	int	cols;
	int	len;

	rows = 0;
	cols = 0;
	while (map[rows])
	{
		len = ft_strlen(map[rows]);
		if (len > cols)
			cols = len;
		rows++;
	}
	cols_rows->rows = rows;
	cols_rows->cols = cols;
}

int	is_ending_map_good(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] != '\0')
			return (0);
		i++;
	}
	return (1);
}
