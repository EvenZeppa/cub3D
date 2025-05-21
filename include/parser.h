#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

/**
 * @brief Fonction principale de parsing du fichier de configuration.
 *
 * Gère la lecture complète du fichier, le parsing des textures, couleurs,
 * et de la carte, puis libère les données de fichier.
 *
 * Quitte le programme avec un message en cas d'erreur à n'importe
 * quelle étape.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @param filename Nom du fichier à parser.
 * @return Toujours 0.
 */
int		parse_file(t_app *app, const char *filename);

/**
 * @brief Parcourt les lignes du fichier et extrait les couleurs sol/plafond.
 *
 * Cherche les préfixes "C " (ceiling) et "F " (floor) dans les lignes du
 * fichier de configuration, puis extrait et stocke les couleurs dans la
 * structure t_app. Utilise parse_rgb() pour convertir les valeurs.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @return Toujours 0.
 */
int		parse_colors(t_app *app);

/**
 * @brief Extrait les chemins des textures depuis les lignes du fichier.
 *
 * Cette fonction parcourt les lignes du fichier de configuration pour
 * détecter les préfixes suivants :
 * - "NO " pour la texture nord
 * - "SO " pour la texture sud
 * - "WE " pour la texture ouest
 * - "EA " pour la texture est
 *
 * Pour chaque préfixe trouvé, la fonction duplique le chemin du fichier
 * texture associé et le stocke dans la structure `file_data`.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @return Toujours 0.
 */
int		parse_textures(t_app *app);

/**
 * @brief Fonction principale pour parser la carte depuis le fichier.
 *
 * Identifie la position de la carte dans le fichier, alloue l’espace
 * nécessaire, copie les lignes, et stocke les dimensions de la carte
 * (lignes et colonnes) dans app->file_data.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @return 0 si succès, 1 en cas d’erreur.
 */
int		parse_map(t_app *app);

/**
 * @brief Fonction principale de validation de la carte du jeu.
 *
 * Cette fonction crée une version rectangulaire de la carte, vérifie que
 * tous les caractères sont valides, qu’il y a exactement un joueur et
 * que la carte est entièrement fermée. En cas d'erreur, elle libère la
 * mémoire et retourne une erreur.
 *
 * @param app Pointeur vers la structure principale de l'application.
 * @return 0 si la carte est valide, -1 en cas d'erreur.
 */
int		check_map(t_app *app);

/**
 * @brief Vérifie si un caractère représente un joueur.
 *
 * Un caractère valide pour le joueur est l'un des suivants :
 * 'N', 'S', 'E' ou 'W'.
 *
 * @param c Caractère à vérifier.
 * @return 1 si le caractère est un joueur, 0 sinon.
 */
int		is_player_char(char c);

/**
 * @brief Vérifie si un caractère est valide pour la carte.
 *
 * Les caractères valides sont : '0', '1', 'N', 'S', 'E', 'W' et ' '.
 *
 * @param c Caractère à valider.
 * @return 1 si valide, 0 sinon.
 */
int		is_valid_map_char(char c);

/**
 * @brief Vérifie si une ligne correspond à une ligne de carte.
 *
 * Une ligne est considérée comme une ligne de carte si elle est
 * composée exclusivement de caractères valides pour la map,
 * et n’est pas vide.
 *
 * @param line Chaîne à analyser.
 * @return 1 si la ligne est une ligne de carte, 0 sinon.
 */
int		is_map_line(const char *line);

/**
 * @brief Calcule les dimensions (lignes et colonnes) de la carte.
 *
 * Parcourt toutes les lignes de la carte pour déterminer la hauteur
 * (nb de lignes) et la largeur maximale (nb de colonnes).
 *
 * @param map Tableau de chaînes représentant la carte.
 * @param cols_rows Pointeur vers la structure recevant les dimensions.
 */
void	calculate_map_dimensions(char **map, t_cols_rows *cols_rows);

#endif
