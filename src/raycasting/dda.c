#include "cub3d.h"

/**
 * @brief Initialise les paramètres de DDA pour le lancer de rayon.
 *
 * Calcule les coordonnées de la cellule de départ sur la grille,
 * les distances à parcourir selon les axes X et Y, ainsi que les
 * étapes (direction du déplacement sur la grille).
 *
 * @param d Pointeur vers la structure t_dda contenant tous les
 * paramètres du rayon.
 */
static void	init_dda(t_dda *d)
{
	d->map_x = (int)d->pos_x;
	d->map_y = (int)d->pos_y;
	d->delta_x = fabs(1.0 / d->dir_x);
	d->delta_y = fabs(1.0 / d->dir_y);
	if (d->dir_x < 0)
	{
		d->step_x = -1;
		d->side_x = (d->pos_x - d->map_x) * d->delta_x;
	}
	else
	{
		d->step_x = 1;
		d->side_x = (d->map_x + 1.0 - d->pos_x) * d->delta_x;
	}
	if (d->dir_y < 0)
	{
		d->step_y = -1;
		d->side_y = (d->pos_y - d->map_y) * d->delta_y;
	}
	else
	{
		d->step_y = 1;
		d->side_y = (d->map_y + 1.0 - d->pos_y) * d->delta_y;
	}
}

/**
 * @brief Effectue la boucle DDA jusqu’à toucher un mur ou sortir de la map.
 *
 * À chaque étape, le rayon progresse vers la cellule suivante dans la
 * direction la plus courte (X ou Y). La boucle s'arrête lorsqu'un mur
 * ('1') est rencontré ou que les limites de la carte sont dépassées.
 *
 * @param d Pointeur vers la structure t_dda.
 * @return 1 si un mur a été touché, 0 si le rayon sort de la carte.
 */
static int	perform_dda_loop(t_dda *d)
{
	while (1)
	{
		if (d->side_x < d->side_y)
		{
			d->side_x += d->delta_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_y += d->delta_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (d->map_x < 0 || d->map_y < 0
			|| d->map_x >= d->map_width || d->map_y >= d->map_height)
			return (0);
		if (d->map[d->map_y][d->map_x] == '1')
			break ;
	}
	return (1);
}

/**
 * @brief Calcule le point d’impact exact du rayon sur un mur.
 *
 * Utilise le côté touché (X ou Y) pour déterminer la distance parcourue
 * par le rayon jusqu’au mur, puis calcule les coordonnées exactes du
 * point d'impact dans le monde réel.
 *
 * @param d Pointeur vers la structure t_dda.
 */
static void	compute_hit(t_dda *d)
{
	if (d->side == 0)
		d->dist = (d->map_x - d->pos_x + (1 - d->step_x) * 0.5) / d->dir_x;
	else
		d->dist = (d->map_y - d->pos_y + (1 - d->step_y) * 0.5) / d->dir_y;
	d->hit_x = d->pos_x + d->dist * d->dir_x;
	d->hit_y = d->pos_y + d->dist * d->dir_y;
}

double	perform_dda_3d(t_dda *d)
{
	init_dda(d);
	if (!perform_dda_loop(d))
		return (-1.0);
	compute_hit(d);
	return (d->dist);
}
