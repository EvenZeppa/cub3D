#include "cub3d.h"

/* Fonction pour transformer la map en version rectangulaire
	Utile pour simplifier le check de la map */
static char	**create_rectangular_grid(char **map, t_cols_rows cols_rows)
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
		if (!grid[i])
			return (NULL);
		memset(grid[i], ' ', cols);
		memcpy(grid[i], map[i], strlen(map[i]));
		grid[i][cols] = '\0';
		i++;
	}
	return (grid);
}

/* Fonction pour version dans une grid si elle est bien entouree de murs */
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

/* Verifie la validite de la map avec les fonction secondaires*/
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
			if (!is_valid_map_char(c))
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

/* Free la grid en fin d'usage */
static void	free_grid(char **grid, int rows)
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

/* Fonction principale pour checker si la map est bien conforme*/
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
	if (check_map_validity(grid, cols_rows, &player_count) != 0)
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
