#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

/**
 * @brief Affiche un message d'erreur, libère les ressources et quitte.
 *
 * Cette fonction affiche un message d'erreur formaté, libère
 * proprement toutes les ressources associées à l'application via
 * `free_game()`, puis termine le programme avec un code d'erreur (1).
 *
 * @param app Pointeur vers la structure principale de l'application.
 * Peut être NULL si aucune ressource à libérer.
 * @param message Message d'erreur à afficher.
 * @return Cette fonction ne retourne jamais, elle appelle exit(1).
 */
int		exit_error(t_app *app, char *message);

/**
 * @brief Libère les ressources graphiques allouées par l'application.
 *
 * Détruit les textures chargées, le framebuffer et la fenêtre via
 * les fonctions `mlx_destroy_image()` et `mlx_destroy_window()`.
 * Appelle ensuite `exit(0)` pour quitter proprement le programme.
 *
 * Cette fonction est conçue pour être utilisée en sortie de programme
 * ou en cas d’erreur critique.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @return 0 après avoir quitté le programme (ne retourne jamais en pratique).
 */
int		free_game(t_app *app);

/**
 * @brief Récupère la largeur maximale d'une carte (nb de colonnes).
 *
 * Parcourt toutes les lignes de la carte et retourne la longueur de
 * la plus longue ligne. Utile pour créer une grille rectangulaire.
 *
 * @param map Tableau de chaînes représentant la carte.
 * @return Largeur maximale de la carte.
 */
int		get_map_width(char **map);

/**
 * @brief Récupère la hauteur d'une carte (nb de lignes).
 *
 * Compte simplement le nombre de lignes non nulles dans le tableau.
 *
 * @param map Tableau de chaînes représentant la carte.
 * @return Nombre de lignes dans la carte.
 */
int		get_map_height(char **map);

/**
 * @brief Calcule l'angle de vue du joueur à partir de sa direction.
 *
 * Utilise `atan2` pour déterminer l'angle entre le vecteur directionnel
 * du joueur et l'axe des abscisses. Corrige les angles négatifs en
 * ajoutant 2π.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @return Angle en radians, compris entre 0 et 2π.
 */
double	get_player_angle(t_app *app);

/**
 * @brief Dessine un pixel sur une image à une position donnée.
 *
 * Remplace la fonction `mlx_pixel_put` avec un accès direct à
 * la mémoire de l’image, pour de meilleures performances.
 * Ne dessine rien si les coordonnées sont hors de l'écran.
 *
 * @param img Pointeur vers l’image cible.
 * @param x Coordonnée horizontale.
 * @param y Coordonnée verticale.
 * @param color Couleur au format entier (0xRRGGBB).
 */
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);

#endif
