/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbonnard <vbonnard@student.42perpignan.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:58:12 by vbonnard          #+#    #+#             */
/*   Updated: 2025/05/21 11:58:12 by vbonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "cub3d.h"

/**
 * @brief Initialise l'application du jeu.
 *
 * Cette fonction configure la structure principale de l'application,
	initialise la bibliothèque MLX,
 * crée la fenêtre du jeu,
	définit les valeurs par défaut pour l'image et les paramètres de la souris,
 * puis initialise successivement la carte,
	les textures et le joueur. Si une étape échoue,
 * elle appelle exit_error avec un message approprié.
 *
 * @param app Pointeur vers la structure de l'application à initialiser.
 * @param map_path Chemin vers le fichier de la carte à charger.
 * @return 0 en cas de succès. Quitte le programme en cas d'échec.
 */
int	init_game(t_app *app, char *map_path);

/**

	* @brief Initialise les textures de l'application en les chargeant
	à partir des chemins de fichiers.
 *
 * Cette fonction tente de charger quatre textures (nord, sud, est,
	ouest) en utilisant les

	* chemins de fichiers spécifiés dans la structure file_data de
	l'application. Si le chargement
 * d'une texture échoue,
	la fonction appelle exit_error avec un message approprié et termine
 * le programme.
 *

	* @param app Pointeur vers la structure de l'application contenant
	les données de textures et de fichiers.
 * @return Retourne toujours 0 en cas de succès.
 */
int	init_textures(t_app *app);

/**

	* @brief Initialise la position et la direction du joueur à partir
	des données de la carte.
 *

	* Cette fonction parcourt la carte stockée dans app->file_data.map
	pour trouver la position
 * de départ du joueur, indiquée par l'un des caractères :
	'N', 'S', 'E' ou 'W'.
 * Une fois trouvée, elle place les coordonnées du joueur (x,
	y) au centre de la case correspondante,
 * et définit le vecteur de direction du joueur (dir_x,
	dir_y) selon l'orientation :
 *   - 'N' : vers le nord (dir_x = 1, dir_y = 0)
 *   - 'S' : vers le sud  (dir_x = -1, dir_y = 0)
 *   - 'E' : vers l'est   (dir_x = 0, dir_y = 1)
 *   - 'W' : vers l'ouest (dir_x = 0, dir_y = -1)

	* Les vitesses de déplacement et de rotation du joueur sont
	également initialisées.
 *

	* @param app Pointeur vers la structure de l'application
	contenant les données du joueur et de la carte.
 * @return 0 si le joueur a été initialisé avec succès,
	1 si aucune position de départ n'a été trouvée.
 */
int	init_player(t_app *app);

/**
 * @brief Initialise la carte pour l'application.
 *

	* Cette fonction vérifie la validité de la carte en
	utilisant la fonction check_map.
 * Si la carte est invalide, elle appelle exit_error
 pour terminer l'application

	* avec un message d'erreur approprié. Retourne 0
	en cas de succès de l'initialisation.
 *

	* @param app Pointeur vers la structure de l'application
		contenant les données de la carte.
	* @return int Retourne 0 en cas de succès.
		Quitte le programme en cas d'échec.
 */
int	init_map(t_app *app);

#endif
