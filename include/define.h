#ifndef DEFINE_H
# define DEFINE_H

// Window dimensions
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

// Map dimensions
# define TILE_SIZE 64

// Input keys
# ifdef __linux__
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

# ifdef __APPLE__
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_ESC 53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# endif

// Player
# define COLLISION_MARGIN 0.1
# define FOV 1.04716666667
# define NUM_RAYS WIN_WIDTH

// Minimap
# define MINIMAP_RADIUS 50  // rayon en pixels
# define MINIMAP_SCALE 8    // 1 case de map = 8 pixels sur la minimap
# define MINIMAP_CENTER_X  (MINIMAP_RADIUS + 10) // position à l’écran
# define MINIMAP_CENTER_Y  (MINIMAP_RADIUS + 10)
# define PLAYER_CIRCLE_RADIUS 5 // rayon du cercle représentant le joueur
# define MINIMAP_BACKGROUND_COLOR 0x202020 // couleur de fond de la minimap
# define MINIMAP_WALL_COLOR 0x888888 // couleur des murs sur la minimap
# define MINIMAP_FLOOR_COLOR 0x444444 // couleur du sol sur la minimap
# define MINIMAP_PLAYER_COLOR 0xFF0000 // couleur du joueur sur la minimap

#endif
