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

char	*get_formatted_line(const char *line)
{
    int i = 0, j = 0;
    int len = strlen(line);
    char *result;
    int in_space = 0;

    // Ignore \n à la fin
    if (len > 0 && line[len - 1] == '\n')
        len--;

    // Skip leading spaces
    while (i < len && isspace((unsigned char)line[i]))
        i++;

    result = malloc(len + 1); // taille max possible, libérable
    if (!result)
        return NULL;

    while (i < len)
    {
        if (isspace((unsigned char)line[i]))
        {
            if (!in_space) // ajoute un seul espace
            {
                result[j++] = ' ';
                in_space = 1;
            }
        }
        else
        {
            result[j++] = line[i];
            in_space = 0;
        }
        i++;
    }

    // Supprimer trailing space final
    if (j > 0 && result[j - 1] == ' ')
        j--;

    result[j] = '\0';
    return result;
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
