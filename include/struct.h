#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cols_rows
{
	int			cols;
	int			rows;
}				t_cols_rows;

typedef struct s_rgb
{
	int			red;
	int			green;
	int			blue;
}				t_rgb;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		move_speed;
	double		rotate_speed;
}				t_player;

typedef struct s_texture
{
	void		*img;
	int			*pixels;
	int			width;
	int			height;
	int			bpp;
}				t_texture;

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
}				t_file_data;

typedef struct s_app
{
	t_file_data	file_data;
	t_player	player;
	t_texture	texture[4];
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}				t_app;

#endif
