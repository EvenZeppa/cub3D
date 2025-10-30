/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:01:33 by vbonnard          #+#    #+#             */
/*   Updated: 2025/05/21 12:01:33 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

/**
 * @brief Rendu complet d’une frame : scène + mini-map.
 *
 * Crée une nouvelle image, effectue le rendu de la scène en 3D puis de
 * la mini-map. Affiche le résultat dans la fenêtre et détruit l'image
 * pour la frame suivante (double buffering manuel).
 *
 * @param app Pointeur vers la structure principale de l'application.
 */
void	render_frame(t_app *app);

/**
 * @brief Dessine une colonne verticale de l’écran pour un rayon donné.
 *
 * Cette fonction trace pixel par pixel la colonne :
 * - le plafond jusqu'à `draw_start`
 * - le mur entre `draw_start` et `draw_end`
 * - le sol au-delà de `draw_end`
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param ray Pointeur vers le rayon correspondant à cette colonne.
 */
void	draw_column(t_app *app, t_ray *ray);

/**
 * @brief Fonction principale de rendu 3D (raycasting + projection).
 *
 * Crée une image si elle n’existe pas encore, puis pour chaque rayon
 * (NUM_RAYS), calcule les informations via DDA et dessine la colonne
 * correspondante dans le framebuffer. Affiche ensuite le résultat
 * dans la fenêtre.
 *
 * @param app Pointeur vers la structure principale de l'application.
 */
void	render_scene(t_app *app);

/**
 * @brief Récupère la couleur d’un pixel dans une texture.
 *
 * Vérifie si la texture est valide et si les coordonnées sont dans
 * les limites. Si elles ne le sont pas, retourne une couleur par
 * défaut (blanc ou rose pour debug). Accède directement à la mémoire
 * pour lire le pixel.
 *
 * @param tex Pointeur vers l’image de texture.
 * @param x Coordonnée horizontale du pixel.
 * @param y Coordonnée verticale du pixel.
 * @return Couleur du pixel (format int RGB).
 */
int		get_texture_pixel(t_image *tex, int x, int y);

/**
 * @brief Sélectionne la texture du mur en fonction de la direction du rayon.
 *
 * En fonction de la direction du rayon et du côté du mur touché (vertical
 * ou horizontal), retourne un pointeur vers la bonne texture :
 * - Nord : textures[0]
 * - Sud : textures[1]
 * - Est  : textures[2]
 * - Ouest: textures[3]
 *
 * @param app Pointeur vers l'application contenant les textures.
 * @param side 0 pour mur vertical, 1 pour mur horizontal.
 * @param ray_dir_x Direction horizontale du rayon.
 * @param ray_dir_y Direction verticale du rayon.
 * @return Pointeur vers la texture à utiliser.
 */
t_image	*choose_wall_texture(t_app *app,
			int side, double ray_dir_x, double ray_dir_y);

/**
 * @brief Fonction principale pour dessiner la mini-map.
 *
 * Initialise les paramètres de la mini-map (centre, échelle, couleurs),
 * puis appelle les fonctions nécessaires pour dessiner le fond, les
 * tiles, et le joueur.
 *
 * @param app Pointeur vers la structure principale de l'application.
 */
void	draw_minimap(t_app *app);

#endif
