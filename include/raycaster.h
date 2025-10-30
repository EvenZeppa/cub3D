/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:58:12 by vbonnard          #+#    #+#             */
/*   Updated: 2025/05/21 11:58:12 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "cub3d.h"

/**
 * @brief Lance un rayon avec l’algorithme DDA pour détecter un mur.
 *
 * Fonction principale du raycasting. Initialise les variables,
 * exécute la boucle DDA, et calcule le point d’impact. Retourne
 * la distance au premier mur rencontré ou -1.0 si aucun mur n’est touché.
 *
 * @param d Pointeur vers la structure t_dda.
 * @return Distance jusqu’au mur rencontré, ou -1.0 si sortie de carte.
 */
double	perform_dda_3d(t_dda *d);

/**
 * @brief Calcule toutes les données d’un rayon à l’écran.
 *
 * Pour chaque colonne de l’écran, calcule l’angle du rayon correspondant,
 * initialise le DDA, exécute l’algorithme de détection de mur, corrige
 * la perspective, et prépare les informations de rendu vertical.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param ray Pointeur vers la structure rayon à remplir.
 * @param i Index de la colonne actuelle à l’écran.
 * @param base_angle Angle de vue central de la caméra.
 */
void	compute_ray_info(t_app *app, t_ray *ray, int i, double base_angle);

#endif
