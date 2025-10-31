/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:58:12 by vbonnard          #+#    #+#             */
/*   Updated: 2025/05/21 11:58:12 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initialise les données nécessaires au DDA à partir du contexte.
 *
 * Récupère la position du joueur, la direction du rayon et les dimensions
 * de la carte pour préparer la structure `t_dda` avant exécution du DDA.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param ray Pointeur vers la structure représentant un rayon.
 * @param dda Pointeur vers la structure DDA à initialiser.
 */
static void	init_dda_data(t_app *app, t_ray *ray, t_dda *dda)
{
	dda->map = app->file_data.map;
	dda->map_width = get_map_width(app->file_data.map);
	dda->map_height = get_map_height(app->file_data.map);
	dda->pos_x = app->player.x;
	dda->pos_y = app->player.y;
	dda->dir_x = ray->dir_x;
	dda->dir_y = ray->dir_y;
}

/**
 * @brief Met à jour les données du rayon après exécution du DDA.
 *
 * Calcule la distance corrigée (projection plan), la hauteur du mur
 * à dessiner, et les bornes de dessin (`draw_start`, `draw_end`) en
 * fonction de la distance du rayon à la caméra.
 *
 * @param ray Pointeur vers la structure représentant un rayon.
 * @param dda Pointeur vers la structure DDA contenant les résultats.
 * @param base_angle Angle initial de la caméra, utilisé pour correction.
 */
static void	fill_ray_from_dda(t_ray *ray, t_dda *dda, double base_angle)
{
	if (dda->dist < 0)
		ray->dist = 0.0001;
	else
		ray->dist = dda->dist;
	ray->side = dda->side;
	ray->hit_x = dda->hit_x;
	ray->hit_y = dda->hit_y;
	ray->corrected_dist = ray->dist * cos(ray->angle - base_angle);
	if (ray->corrected_dist < 0.0001)
		ray->corrected_dist = 0.0001;
	ray->wall_height = (int)(WIN_HEIGHT / ray->corrected_dist);
	ray->draw_start = -ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

void	compute_ray_info(t_app *app, t_ray *ray, int i, double base_angle)
{
	t_dda	dda;

	ray->angle = base_angle - (FOV / 2) + ((double)i / NUM_RAYS) * FOV;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	init_dda_data(app, ray, &dda);
	dda.dist = perform_dda_3d(&dda);
	fill_ray_from_dda(ray, &dda, base_angle);
	ray->screen_x = i * (WIN_WIDTH / NUM_RAYS);
}
