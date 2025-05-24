#include "cub3d.h"

void	free_file_data(t_app *app)
{
	int	i;

	if (!app || !app->file_data.file_data)
		return ;
	i = 0;
	while (app->file_data.file_data[i])
	{
		free(app->file_data.file_data[i]);
		i++;
	}
	free(app->file_data.file_data);
	if (app->file_data.map)
		free_grid(app->file_data.map, app->file_data.rows);
	if (app->file_data.texture_north)
		free(app->file_data.texture_north);
	if (app->file_data.texture_south)
		free(app->file_data.texture_south);
	if (app->file_data.texture_east)
		free(app->file_data.texture_east);
	if (app->file_data.texture_west)
		free(app->file_data.texture_west);
}

/* Fonction pour liberer les donnees sur la heap */
int	free_game(t_app *app)
{
	int	i;

	if (!app)
		return (exit(0), 1);
	i = 0;
	while (i < 4)
	{
		if (app->textures[i].img)
			mlx_destroy_image(app->mlx, app->textures[i].img);
		i++;
	}
	free_file_data(app);
	if (app->frame.img)
		mlx_destroy_image(app->mlx, app->frame.img);
	if (app->win)
		mlx_destroy_window(app->mlx, app->win);
	return (exit(0), 0);
}
