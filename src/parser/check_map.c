#include "cub3d.h"

/**
 * @brief Libère la mémoire allouée pour une grille de carte.
 *
 * Parcourt chaque ligne du tableau et la libère avant de
 * libérer le tableau lui-même.
 *
 * @param grid Grille allouée dynamiquement.
 * @param rows Nombre de lignes à libérer.
 */
void	free_grid(char **grid, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

/**
 * @brief Crée une grille rectangulaire à partir de la carte originale.
 *
 * Cette fonction prend une carte de taille variable (lignes de longueurs
 * différentes) et la convertit en une grille rectangulaire remplie d'espaces,
 * ce qui permet une vérification uniforme de la carte.
 *
 * @param map Carte initiale sous forme de tableau de chaînes.
 * @param cols_rows Dimensions (colonnes et lignes) de la grille finale.
 * @return Grille rectangulaire allouée dynamiquement ou NULL en cas d’échec.
 */
char	**create_rectangular_grid(char **map, t_cols_rows cols_rows)
{
	int		rows;
	int		cols;
	char	**grid;
	int		i;

	rows = cols_rows.rows;
	cols = cols_rows.cols;
	grid = malloc(sizeof(char *) * rows);
	if (!grid)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		grid[i] = malloc(cols + 1);
		if (!grid[i] || (map[i][0] == '\n' && !is_ending_map_good(&map[i])))
			return (free_grid(grid, i), NULL);
		ft_memset(grid[i], ' ', cols);
		ft_memcpy(grid[i], map[i], ft_strlen(map[i]));
		grid[i][cols] = '\0';
		i++;
	}
	return (grid);
}

/**
 * @brief Vérifie les cellules voisines d'une position pour la validité.
 *
 * Cette fonction vérifie que les 4 cases adjacentes (haut, bas, gauche,
 * droite) ne sont pas des espaces vides, ce qui indiquerait une faille
 * potentielle dans l'encadrement de la carte.
 *
 * @param grid Grille rectangulaire représentant la carte.
 * @param row Ligne actuelle.
 * @param col Colonne actuelle.
 * @param cols_rows Dimensions de la grille.
 * @return 1 si les cellules voisines sont valides, 0 sinon.
 */
static int	check_surrounding_cells(char **grid,
	int row, int col, t_cols_rows cols_rows)
{
	const int	dx[] = {-1, 1, 0, 0};
	const int	dy[] = {0, 0, -1, 1};
	t_cols_rows	xy;
	int			i;

	i = 0;
	while (i < 4)
	{
		xy.rows = row + dx[i];
		xy.cols = col + dy[i];
		if (xy.rows < 0 || xy.rows >= cols_rows.rows
			|| xy.cols < 0 || xy.cols >= cols_rows.cols)
			return (0);
		if (grid[xy.rows][xy.cols] == ' ')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Vérifie si la grille est valide selon les règles du jeu.
 *
 * Cette fonction vérifie les caractères autorisés, les positions valides
 * pour le joueur et les cellules ouvertes ('0'). Elle s'assure également
 * qu'il y a exactement un joueur et que toutes les cellules ouvertes ou
 * de départ sont bien entourées.
 *
 * @param grid Grille rectangulaire de la carte.
 * @param cols_rows Dimensions de la grille.
 * @param player_count Pointeur vers un compteur de joueurs trouvés.
 * @return 0 si la carte est valide, 1 en cas d’erreur.
 */
static int	check_map_validity(char **grid,
	t_cols_rows cols_rows, int *player_count)
{
	int		i;
	int		j;
	char	c;

	i = -1;
	while (++i < cols_rows.rows)
	{
		j = -1;
		while (++j < cols_rows.cols)
		{
			c = grid[i][j];
			if (!is_valid_map_char(c) && c != '\n')
				return (1);
			if (is_player_char(c))
			{
				(*player_count)++;
				if (!check_surrounding_cells(grid, i, j, cols_rows))
					return (1);
			}
			else if (c == '0'
				&& !check_surrounding_cells(grid, i, j, cols_rows))
				return (1);
		}
	}
	return (0);
}

int	check_map(t_app *app)
{
	t_cols_rows	cols_rows;
	int			player_count;
	char		**map;
	char		**grid;

	player_count = 0;
	map = app->file_data.map;
	calculate_map_dimensions(map, &cols_rows);
	grid = create_rectangular_grid(map, cols_rows);
	if (!grid)
		return (-1);
	if (check_map_validity(grid, cols_rows, &player_count) != 0
		|| check_spaces(grid, cols_rows) != 0)
	{
		free_grid(grid, cols_rows.rows);
		return (-1);
	}
	if (player_count != 1)
	{
		free_grid(grid, cols_rows.rows);
		return (-1);
	}
	free_grid(grid, cols_rows.rows);
	return (0);
}
