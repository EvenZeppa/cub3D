#ifndef DEFINE_H
# define DEFINE_H

// Window dimensions
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// Minimap dimensions
# define MINIMAP_SCALE 0.2
# define MINIMAP_TILE (TILE_SIZE * MINIMAP_SCALE)
# define MINIMAP_SIZE 200

// Map dimensions
# define TILE_SIZE 64

// Input keys
# ifdef __linux__
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
#endif

# ifdef __APPLE__
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# endif

#endif
