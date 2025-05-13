#include "cub3d.h"

int	get_map_width(char **map)
{
	int max = 0;
	int i = 0;
	while (map[i])
	{
		int len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	get_map_height(char **map)
{
	int i = 0;
	while (map[i])
		i++;
	return (i);
}
