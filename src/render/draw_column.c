#include "cub3d.h"

static void	draw_ceiling_pixel(t_app *app, t_ray *ray, int y)
{
	int	color;

	color = (app->file_data.ceiling.red << 16)
		| (app->file_data.ceiling.green << 8)
		| app->file_data.ceiling.blue;
	my_mlx_pixel_put(&app->frame, ray->screen_x, y, color);
}

static void	draw_floor_pixel(t_app *app, t_ray *ray, int y)
{
	int	color;

	color = (app->file_data.floor.red << 16)
		| (app->file_data.floor.green << 8)
		| app->file_data.floor.blue;
	my_mlx_pixel_put(&app->frame, ray->screen_x, y, color);
}

static void	draw_wall_pixel(t_app *app, t_ray *ray, int y)
{
	t_image	*tex;
	double	wall_x;
	int		d;

	tex = choose_wall_texture(app, ray->side, ray->dir_x, ray->dir_y);
	if (!tex || !tex->addr)
		return ;
	if (ray->side == 0)
		wall_x = ray->hit_y;
	else
		wall_x = ray->hit_x;
	wall_x -= floor(wall_x);
	if (wall_x < 0.0)
		wall_x = 0.0;
	if (wall_x > 1.0)
		wall_x = 1.0;
	ray->tex_x = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		ray->tex_x = tex->width - ray->tex_x - 1;
	d = y * 256 - WIN_HEIGHT * 128 + ray->wall_height * 128;
	ray->tex_y = ((d * tex->height) / ray->wall_height) / 256;
	my_mlx_pixel_put(&app->frame, ray->screen_x, y,
		get_texture_pixel(tex, ray->tex_x, ray->tex_y));
}

void	draw_column(t_app *app, t_ray *ray)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < ray->draw_start)
			draw_ceiling_pixel(app, ray, y);
		else if (y >= ray->draw_start && y <= ray->draw_end)
			draw_wall_pixel(app, ray, y);
		else
			draw_floor_pixel(app, ray, y);
		y++;
	}
}
