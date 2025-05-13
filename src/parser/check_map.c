#include "cub3d.h"

static int	check_surroundings(char **map, int row, int col, int rows, int cols)
{
	// Coordonnées autour
	const int dx[] = {-1, 1, 0, 0};
	const int dy[] = {0, 0, -1, 1};
	int i, x, y;

	for (i = 0; i < 4; i++)
	{
		x = row + dx[i];
		y = col + dy[i];
		if (x < 0 || x >= rows || y < 0 || y >= cols)
			return (0); // bord du tableau = pas fermé
		if (map[x][y] == ' ')
			return (0); // adjacent à un espace = erreur
	}
	return (1);
}

int	check_map(t_app *app)
{
	char	**map = app->file_data.map;
	int		rows = 0, cols = 0;
	int		player_count = 0;
	int		i, j;

	// Calcul du nombre de lignes et max longueur
	while (map[rows])
	{
		int len = strlen(map[rows]);
		if (len > cols)
			cols = len;
		rows++;
	}

	// Créer une copie rectangulaire
	char **grid = malloc(sizeof(char *) * rows);
	if (!grid)
		return (-1);

	for (i = 0; i < rows; i++)
	{
		grid[i] = malloc(cols + 1);
		if (!grid[i])
			return (-1);
		memset(grid[i], ' ', cols);
		memcpy(grid[i], map[i], strlen(map[i]));
		grid[i][cols] = '\0';
	}

	// Vérification
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			char c = grid[i][j];
			if (!is_valid_map_char(c))
				return (fprintf(stderr, "Invalid character in map: %c\n", c), -1);
			if (is_player_char(c))
			{
				player_count++;
				if (!check_surroundings(grid, i, j, rows, cols))
					return (fprintf(stderr, "Map not closed around player at %d,%d\n", i, j), -1);
			}
			else if (c == '0')
			{
				if (!check_surroundings(grid, i, j, rows, cols))
					return (fprintf(stderr, "Map not closed around space at %d,%d\n", i, j), -1);
			}
		}
	}

	if (player_count != 1)
		return (fprintf(stderr, "Map must have exactly one player start\n"), -1);

	// Free temporaire
	for (i = 0; i < rows; i++)
		free(grid[i]);
	free(grid);

	return (0);
}
