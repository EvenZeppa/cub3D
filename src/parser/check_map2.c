#include "cub3d.h"

// Recursively marks all connected ' ' (space) cells starting
// from (x, y) as 'F' to tag outside area.
// Stops recursion if out of bounds,
// cell is not a space, or already marked as 'F'.
static void	mark_outside(char **grid, int x, int y, t_cols_rows dim)
{
	if (x < 0 || x >= dim.rows || y < 0 || y >= dim.cols)
		return ;
	if (grid[x][y] != ' ')
		return ;
	if (grid[x][y] == 'F')
		return ;
	grid[x][y] = 'F';
	mark_outside(grid, x + 1, y, dim);
	mark_outside(grid, x - 1, y, dim);
	mark_outside(grid, x, y + 1, dim);
	mark_outside(grid, x, y - 1, dim);
}

// Creates a copy of the grid with all outside areas tagged as 'F'.
char	**tag_outside_area(char **grid, t_cols_rows dim)
{
	char	**copy;
	int		i;

	copy = create_rectangular_grid(grid, dim);
	if (!copy)
		return (NULL);
	i = 0;
	while (i < dim.rows)
	{
		mark_outside(copy, i, 0, dim);
		mark_outside(copy, i, dim.cols - 1, dim);
		i++;
	}
	i = 0;
	while (i < dim.cols)
	{
		mark_outside(copy, 0, i, dim);
		mark_outside(copy, dim.rows - 1, i, dim);
		i++;
	}
	return (copy);
}

// Checks if the cell at (x, y) in the marked grid is inside the border.
int	is_inside_border(char **marked, int x, int y)
{
	return (marked[x][y] != 'F');
}

// Checks if there are any spaces (' ') inside the border of the map.
int	check_spaces(char **grid, t_cols_rows cols_rows)
{
	char	**marked;
	int		i;
	int		j;

	marked = tag_outside_area(grid, cols_rows);
	if (!marked)
		return (1);
	i = 0;
	while (i < cols_rows.rows)
	{
		j = 0;
		while (j < cols_rows.cols)
		{
			if (grid[i][j] == ' ' && is_inside_border(marked, i, j))
			{
				free_grid(marked, cols_rows.rows);
				return (1);
			}
			j++;
		}
		i++;
	}
	free_grid(marked, cols_rows.rows);
	return (0);
}
