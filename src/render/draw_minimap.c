#include "cub3d.h"

/**
 * @brief Dessine un seul tile (mur ou sol) de la mini-map.
 *
 * Calcule les coordonnées du tile sur la carte en fonction du décalage
 * et de l'échelle. Ignore les coordonnées hors limites ou les espaces
 * vides. Applique la couleur selon le type de tile (mur ou sol).
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param mm Pointeur vers la structure de la mini-map.
 * @param dx Décalage horizontal depuis le centre de la mini-map.
 * @param dy Décalage vertical depuis le centre de la mini-map.
 */
static void	draw_tile(t_app *app, t_minimap *mm, int dx, int dy)
{
	int		tile_x;
	int		tile_y;
	char	tile;
	int		color;

	tile_x = (int)(app->player.x + dx / (double)mm->scale);
	tile_y = (int)(app->player.y + dy / (double)mm->scale);
	if (tile_y < 0 || tile_y >= get_map_height(app->file_data.map))
		return ;
	if (tile_x < 0 || tile_x >= get_map_width(app->file_data.map))
		return ;
	tile = app->file_data.map[tile_y][tile_x];
	if (tile == ' ' || tile == '\0' || tile == '\n')
		return ;
	if (tile == '1')
		color = mm->wall_color;
	else
		color = mm->floor_color;
	my_mlx_pixel_put(&app->frame, mm->center_x + dx, mm->center_y + dy, color);
}

/**
 * @brief Dessine le fond de la mini-map et tous les tiles visibles.
 *
 * Parcourt tous les pixels dans un cercle autour du joueur. Pour chaque
 * pixel, dessine la couleur de fond, puis appelle `draw_tile()` pour
 * dessiner le contenu de la carte (murs/sols).
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param mm Pointeur vers la structure de la mini-map.
 */
static void	draw_minimap_background(t_app *app, t_minimap *mm)
{
	int	r2;
	int	dy;
	int	dx;

	r2 = mm->radius * mm->radius;
	dy = -mm->radius;
	dx = 0;
	while (dy <= mm->radius)
	{
		dx = -mm->radius;
		while (dx <= mm->radius)
		{
			if (dx * dx + dy * dy <= r2)
			{
				my_mlx_pixel_put(&app->frame,
					mm->center_x + dx, mm->center_y + dy, mm->background_color);
				draw_tile(app, mm, dx, dy);
			}
			dx++;
		}
		dy++;
	}
}

/**
 * @brief Dessine le joueur comme un cercle au centre de la mini-map.
 *
 * Dessine un cercle rempli autour du centre défini dans `mm`, en utilisant
 * `player_radius` et `player_color` pour représenter le joueur.
 *
 * @param frame Framebuffer cible (frame principal de l'application).
 * @param mm Structure de la mini-map contenant les infos du joueur.
 */
static void	draw_player(t_image *frame, t_minimap mm)
{
	int	r2;
	int	dy;
	int	dx;

	r2 = mm.player_radius * mm.player_radius;
	dx = 0;
	dy = -mm.player_radius;
	while (dy <= mm.player_radius)
	{
		dx = -mm.player_radius;
		while (dx <= mm.player_radius)
		{
			if (dx * dx + dy * dy <= r2)
				my_mlx_pixel_put(frame, mm.center_x + dx,
					mm.center_y + dy, mm.player_color);
			dx++;
		}
		dy++;
	}
}

void	draw_minimap(t_app *app)
{
	t_minimap	mm;

	mm.center_x = MINIMAP_CENTER_X;
	mm.center_y = MINIMAP_CENTER_Y;
	mm.radius = MINIMAP_RADIUS;
	mm.scale = MINIMAP_SCALE;
	mm.background_color = MINIMAP_BACKGROUND_COLOR;
	mm.wall_color = MINIMAP_WALL_COLOR;
	mm.floor_color = MINIMAP_FLOOR_COLOR;
	mm.player_color = MINIMAP_PLAYER_COLOR;
	mm.player_radius = PLAYER_CIRCLE_RADIUS;
	draw_minimap_background(app, &mm);
	draw_player(&app->frame, mm);
}
