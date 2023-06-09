/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 21:16:51 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/05/09 21:31:24 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_textures
{
	SO,
	NO,
	WE,
	EA,
}	t_textures;

typedef struct s_window
{
	void	*win_ptr;
	int		width;
	int		height;
}	t_window;

typedef struct s_image
{
	void	*addr;
	int		width;
	int		height;
	int		x;
	int		y;
}	t_image;

typedef struct s_rectangle
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}	t_rectangle;

typedef struct s_line
{
	int		begin_x;
	int		begin_y;
	int		end_x;
	int		end_y;
	int		color;
	int		pixels;
	int		delta_x;
	int		delta_y;
	double	pixel_x;
	double	pixel_y;
}	t_line;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		*color_buffer;
}	t_img;

typedef struct s_game
{
	void		*mlx_ptr;
	char		**map;
	int			moves;
	int			collectibles;
	t_window	window;
	t_image		wall;
	t_image		space;
	t_image		tux;
	t_image		coin;
	t_image		door;
	t_img		img;
	t_img		img2;
}	t_game;

typedef struct s_file
{
	char	*name;
	int		fd;
}	t_file;

typedef struct s_cord
{
	int	x;
	int	y;
}	t_cord;

typedef struct s_map_dimensions
{
	int		columns;
	int		rows;
	int		col_offset;
}	t_map_dimensions;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		alpha;
	char	*color_str;
}	t_color;

typedef struct s_map
{
	t_map_dimensions	dimensions;
	t_list				*map_list;
	char				**map_matrix;
	t_file				map_file;
	char				*no_file;
	char				*so_file;
	char				*we_file;
	char				*ea_file;
	t_color				floor_color;
	t_color				ceiling_color;
	int					found_player;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		turn_direction;
	int		walk_direction;
	int		walk_side_direction;
	double	rotation_angle;
	double	walk_speed;
	double	turn_speed;
	t_line	*line;
	char	player_char;
}	t_player;

typedef struct s_ray
{
	double		ray_angle;
	double		wall_hit_x;
	double		wall_hit_y;
	double		distance;
	int			has_hit_vertical;
	t_textures	texture;
}	t_ray;

typedef struct s_intersection
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	next_x;
	double	next_y;
	double	wall_hit_x;
	double	wall_hit_y;
	double	x_to_check;
	double	y_to_check;
	double	distance;

}	t_intersection;

typedef struct s_wall
{
	int	wall_top_pixel;
	int	wall_bottom_pixel;
	int	wall_height;
	int	text_offset_x;
	int	text_offset_y;
	int	dist_from_top;
	int	color;
	int	text_num;

}	t_wall;

typedef struct s_coordinates
{
	double	x;
	double	y;
}	t_coordinates;

typedef struct s_cubd
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_game		*game;
	t_player	*player;
	t_ray		rays[NUM_RAYS];
	t_img		img_game;
	t_img		textures[4];
}	t_cubd;

#endif
