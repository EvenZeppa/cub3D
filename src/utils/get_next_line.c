#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	len = ft_strlen(s);
	char	*dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		dup[i] = s[i];
	dup[len] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1 = s1 ? ft_strlen(s1) : 0;
	size_t	len2 = s2 ? ft_strlen(s2) : 0;
	char	*joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	size_t i = 0;
	for (; i < len1; i++)
		joined[i] = s1[i];
	for (size_t j = 0; j < len2; j++)
		joined[i++] = s2[j];
	joined[i] = '\0';
	return (joined);
}



char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	if (!s)
		return (NULL);
	size_t	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	char *sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		sub[i] = s[start + i];
	sub[len] = '\0';
	return (sub);
}

char	*read_and_append(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes;
	char	*temp;

	bytes = 1;
	if (!stash)
		stash = ft_strdup("");
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stash), NULL);
		buffer[bytes] = '\0';
		temp = stash;
		stash = ft_strjoin(temp, buffer);
		free(temp);
	}
	return (stash);
}


char	*extract_line(char *stash)
{
	int		len = 0;
	char	*line;

	if (!stash || !stash[0])
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	for (int i = 0; i < len; i++)
		line[i] = stash[i];
	line[len] = '\0';
	return (line);
}

char	*trim_stash(char *stash)
{
	int		i = 0, j = 0;
	char	*new_stash;

	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++; // Skip the '\n'
	new_stash = malloc(ft_strlen(stash + i) + 1);
	if (!new_stash)
		return (free(stash), NULL);
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}



char	*get_next_line(int fd)
{
	static char *stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	stash = read_and_append(fd, stash);
	if (!stash)
		return (NULL);

	line = extract_line(stash);
	stash = trim_stash(stash);
	return (line);
}


