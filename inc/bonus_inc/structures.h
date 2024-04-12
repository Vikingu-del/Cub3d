/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:25:48 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 18:05:14 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdbool.h>
# include "libft.h"

# define X 0
# define Y 1
# define PLAYER_SPEED 0.05
# define PLAYER_ROT_SPEED 0.05
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 4
# define C 5
# define START 0
# define END 1
# define OLD 0
# define NEW 1
# define TEXT_SIZE 64
# define LIFE_S 0
# define KEY_STATUS 1
# define ENEMY 0
# define KEY 1
# define DOOR 2

enum	e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct s_point
{
	float	x;
	float	y;
	int		color;
}		t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		*casted_addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx
{
	int		width;
	int		height;
	int		default_w;
	int		default_h;
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;

typedef struct s_map
{
	char	*texture[6];
	char	**map_file;
	char	**map;
	int		map_width;
	int		map_height;
	int		num_line;
	int		num_textures;
	int		map_x;
	int		map_y;
	int		key[2];
	int		enemy[2];
	int		door[2];
}				t_map;

typedef struct s_vec
{
	double	dir[2];
}		t_vec;

typedef struct s_ray
{
	double	camera_x;
	t_vec	ray_dir;
	t_vec	ray_dir_l;
	t_vec	ray_dir_r;
	int		map_point[2];
	int		step[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw[2];
	int		hit_door;
}	t_ray;

typedef struct s_player
{
	double	pos[2];
	t_point	m_pos;
	t_vec	front;
	t_vec	cam;
	int		move[2];
	double	rotate;
	double	player_speed;
	double	player_rot_speed;
	char	init_v;
	float	fov;
	int		info[2];
	t_ray	ray;
}			t_player;

typedef struct s_textures
{
	t_img	img_text[6];
	int		*textures[6];
	int		text_point[2];
	double	tex_step;
	double	tex_pos;
	int		tex_size;
}		t_textures;

typedef struct s_keys
{
	int		key_esc;
	int		key_s;
	int		key_w;
	int		key_a;
	int		key_d;
	int		key_left;
	int		key_right;
	int		key_i;
	int		key_o;
}				t_keys;

typedef struct s_minimap
{
	char	**map;
	t_point	m_pos;
	t_img	*img;
	int		view_dist;
	int		size;
	int		map_lines;
	int		longest_line;
	int		offset_x;
	int		offset_y;
	int		x;
	int		y;
	int		tile_size;
	int		show;
	int		key_status;
}			t_minimap;

typedef struct s_sprite_tex
{
	t_img		img;
	int			*pixels;
	double		text_point[2];
	double		text_pos[2];
	double		tex_step;
	double		tex_pos;
	double		inv_det;
	int			tex_size;
	double		transform[2];
	int			start[2];
	int			end[2];
	int			h;
	int			w;
	int			d;
	int			color;
	int			tex_x;
	int			screen_x;
}				t_sprite_tex;

typedef struct s_sprite
{
	t_sprite_tex	sprite_text[3];
	int				sprite_order[2];
	double			sprite_dist[2];
}				t_sprite;

typedef struct s_cube
{
	t_mlx			screen;
	t_player		player;
	t_map			map;
	t_textures		wall_text;
	t_img			minimap;
	t_minimap		minimap_data;
	t_keys			key;
	t_sprite		sprite;
	int				**text_pixels;
	int				player_has_moved;
	int				game_status;
	int				key_status;
	int				door;
}			t_cube;

typedef struct s_text_info
{
	t_img	*img;
	void	*mlx;
	char	*path;
	t_cube	*cube;
	int		**tx;
}		t_text_info;

typedef struct s_floor_info
{
	int		p;
	double	pos_z;
	double	row_distance;
	double	floor_step[2];
	double	floor[2];
	int		x;
	int		cell[2];
	int		t[2];
}				t_floor_info;

typedef struct s_sprite_info
{
	int				m_h;
	int				m_w;
	t_sprite_tex	sprite_text;
	char			**m;
	t_cube			*c;
	double			*z_b;
}				t_sprite_info;

#endif
