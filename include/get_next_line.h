#ifndef GNL_H
# define GNL_H

#include <unistd.h>
#include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*extract_line(char *stash);
char	*trim_stash(char *stash);
char	*read_and_append(int fd, char *stash);
char	*get_next_line(int fd);

#endif