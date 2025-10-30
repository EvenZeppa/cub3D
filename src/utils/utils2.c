#include "cub3d.h"

static int	skip_leading_spaces(const char *line, int len)
{
	int	i;

	i = 0;
	while (i < len && isspace((unsigned char)line[i]))
		i++;
	return (i);
}

static int	get_trimmed_length(const char *line, int len)
{
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}

char	*get_formatted_line(const char *line)
{
	int		i;
	int		j;
	char	*result;

	result = malloc(ft_strlen(line) + 1);
	if (!result)
		return (NULL);
	i = skip_leading_spaces(line, get_trimmed_length(line, ft_strlen(line)));
	j = 0;
	while (line[i] && line[i] != '\n')
	{
		if (isspace((unsigned char)line[i]))
		{
			if (j > 0 && result[j - 1] != ' ')
				result[j++] = ' ';
		}
		else
			result[j++] = line[i];
		i++;
	}
	if (j > 0 && result[j - 1] == ' ')
		j--;
	result[j] = '\0';
	return (result);
}

/* Sort du programme en y affichant une erreur */
int	exit_error(t_app *app, char *message)
{
	printf("Error\n%s\n", message);
	free_game(app);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}