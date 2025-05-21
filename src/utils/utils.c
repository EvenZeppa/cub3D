#include "cub3d.h"

int	get_map_width(char **map)
{
	int	max;
	int	i;
	int	len;

	max = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

double	get_player_angle(t_app *app)
{
	double	angle;

	angle = atan2(app->player.dir_y, app->player.dir_x);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

char	*ft_strldup(const char *s, size_t size)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * size);
	if (!ptr)
		return (ptr);
	ft_strlcpy(ptr, s, size);
	return (ptr);
}
