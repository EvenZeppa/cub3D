/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:58:12 by vbonnard          #+#    #+#             */
/*   Updated: 2025/05/21 11:58:12 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "cub3d.h"

/**
 * @brief Gère le mouvement de la souris pour faire pivoter
 * la direction du joueur.
 *
 * Cette fonction est appelée à chaque mouvement de la souris. Elle
 * calcule la différence de position horizontale de la souris (delta_x)
 * depuis la dernière position enregistrée, puis ajuste l'angle de
 * direction du joueur en conséquence, en appliquant une sensibilité
 * définie par app->mouse_sensitivity.
 *
 * Si la souris n'a pas encore été initialisée, la fonction enregistre
 * simplement la position actuelle et retourne. Elle ignore également
 * les mouvements anormaux (sauts importants) pour éviter des rotations
 * inattendues.
 *
 * @param x Position horizontale actuelle de la souris.
 * @param y Position verticale actuelle de la souris (ignorée).
 * @param app Pointeur vers la structure principale de l'application.
 * @return Toujours 0.
 */
int		mouse_move(int x, int y, t_app *app);

/**
 * @brief Gère les événements de pression de touche.
 *
 * Vérifie le code de la touche pressée et appelle la fonction
 * appropriée : déplacement (avant, arrière, gauche, droite),
 * rotation (gauche, droite), ou quitter (Échap).
 *
 * @param keycode Le code de la touche pressée.
 * @param app Pointeur vers la structure principale de l'application.
 * @return Toujours 0.
 */
int		key_press(int keycode, t_app *app);

/**
 * @brief Déplace le joueur vers l'avant.
 *
 * Avance dans la direction actuelle du joueur. Vérifie les
 * collisions avec la carte (murs = '1') en appliquant une marge.
 *
 * @param app Pointeur vers la structure principale de l'application.
 */
void	move_forward(t_app *app);

/**
 * @brief Déplace le joueur vers l'arrière.
 *
 * Recule dans la direction opposée au regard. Vérifie les
 * collisions avec les murs.
 *
 * @param app Pointeur vers la structure principale de l'application.
 */
void	move_backward(t_app *app);

/**
 * @brief Déplace le joueur vers la droite (strafe).
 *
 * Déplacement perpendiculaire au regard, vers la droite.
 * Vérifie les collisions avec les murs.
 *
 * @param app Pointeur vers la structure principale de l'application.
 */
void	move_right(t_app *app);

/**
 * @brief Déplace le joueur vers la gauche (strafe).
 *
 * Déplacement perpendiculaire au regard, vers la gauche.
 * Vérifie les collisions avec les murs.
 *
 * @param app Pointeur vers la structure principale de l'application.
 */
void	move_left(t_app *app);

/**
 * @brief Fait pivoter le joueur vers la gauche.
 *
 * Applique une rotation antihoraire au vecteur de direction.
 *
 * @param app Pointeur vers la structure principale de l'application.
 */
void	rotate_left(t_app *app);

/**
 * @brief Fait pivoter le joueur vers la droite.
 *
 * Applique une rotation horaire au vecteur de direction.
 *
 * @param app Pointeur vers la structure principale de l'application.
 */
void	rotate_right(t_app *app);

#endif
