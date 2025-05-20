#ifndef STRUCT_H
# define STRUCT_H

// Stores the number of columns and rows in the map.
typedef struct s_cols_rows
{
	int			cols;
	int			rows;
}				t_cols_rows;

// Holds all variables needed
// for the DDA (Digital Differential Analyzer) algorithm.
typedef struct s_dda
{
	// Inputs
	char		**map;
	int			map_width;
	int			map_height;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;

	// Interns
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		side_x;
	double		side_y;
	double		delta_x;
	double		delta_y;

	// Outputs
	int			side;
	double		hit_x;
	double		hit_y;
	double		dist;
}	t_dda;

// Stores information about a single ray for raycasting.
typedef struct s_ray
{
	double	angle;
	double	dir_x;
	double	dir_y;
	double	dist;
	double	corrected_dist;
	double	hit_x;
	double	hit_y;
	int		side;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		screen_x;
	int		tex_x;
	int		tex_y;
}	t_ray;

// Represents an RGB color.
typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

// Stores player position, direction, and movement parameters.
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	angle;
	double	move_speed;
	double	rotate_speed;
}				t_player;

// Represents an image or texture.
typedef struct s_image
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			size_line;
	int			endian;
}				t_image;

// Stores all data loaded from the configuration file,
// including textures and map.
typedef struct s_file_data
{
	char		**file_data;
	int			lines_count;
	void		*texture_north;
	void		*texture_south;
	void		*texture_east;
	void		*texture_west;
	t_rgb		ceiling;
	t_rgb		floor;
	char		**map;
	int			cols;
	int			rows;
}				t_file_data;

// Represents the minimap configuration.
typedef struct s_minimap
{
	int	center_x;
	int	center_y;
	int	radius;
	int	scale;
	int	background_color;
	int	wall_color;
	int	floor_color;
	int	player_color;
	int	player_radius;
}	t_minimap;

// Main application structure holding all game state.
typedef struct s_app
{
	t_file_data	file_data;
	t_player	player;
	t_image		textures[4];
	t_image		frame;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_app;

#endif
