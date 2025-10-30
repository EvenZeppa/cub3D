#include "cub3d.h"

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
		if (!grid[i] || (map[i][0] == '\n'))
			return (free_grid(grid, i + 1), NULL);
		ft_memset(grid[i], ' ', cols);
		ft_memcpy(grid[i], map[i], ft_strlen(map[i]) - 1);
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
			|| xy.cols < 0 || xy.cols >= cols_rows.cols - 1)
			return (0);
		if (grid[xy.rows][xy.cols] == ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	validate_cell(t_app *app, t_mapcheck m, int i, int j)
{
	char	c;

	c = m.grid[i][j];
	if (!is_valid_map_char(c) && c != '\n')
		return (free_grid(m.grid, m.cr.rows),
			exit_error(app, "Invalid map character"), 1);
	if (is_player_char(c))
	{
		(*m.player_count)++;
		if (!check_surrounding_cells(m.grid, i, j, m.cr))
			return (free_grid(m.grid, m.cr.rows),
				exit_error(app, "Invalid player position"), 1);
	}
	else if (c == '0' && !check_surrounding_cells(m.grid, i, j, m.cr))
		return (free_grid(m.grid, m.cr.rows),
			exit_error(app, "Invalid open space"), 1);
	return (0);
}

static int	check_map_validity(t_app *app, char **grid,
								t_cols_rows cr, int *player_count)
{
	t_mapcheck	m;
	int			i;
	int			j;

	m.grid = grid;
	m.cr = cr;
	m.player_count = player_count;
	i = -1;
	while (++i < cr.rows)
	{
		j = -1;
		while (++j < cr.cols)
			if (validate_cell(app, m, i, j))
				return (1);
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
		exit_error(app, "Invalid map");
	check_map_validity(app, grid, cols_rows, &player_count);
	if (check_spaces(grid, cols_rows) != 0)
	{
		free_grid(grid, cols_rows.rows);
		exit_error(app, "Invalid spaces in map");
	}
	if (player_count != 1)
	{
		free_grid(grid, cols_rows.rows);
		exit_error(app, "Invalid player count");
	}
	free_grid(grid, cols_rows.rows);
	return (0);
}
