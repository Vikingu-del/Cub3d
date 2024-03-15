/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:40:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 17:26:48 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include "structures.h"
# include <math.h>
# include "libft.h"
# include "error.h"
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/Xlib.h>

# ifdef __APPLE__
#  include "../lib/mlx_mac/mlx.h"
#  include "keycodes_mac.h"
#  define PLATFORM "mac"
# else
#  include "../lib/mlx_linux/mlx.h"
#  include "keycodes_linux.h"
#  define PLATFORM "linux"
# endif

# define MAX_LINES 10000

# define EXPAND 1
# define REDUCE 0

# define MAPSCALE 64
# define MINIMAPSCALE 5
# define MAX_NUM_TEXT 6
# define COLORS_COMPONENTS 3
# define MMAP_VIEW_DIST 4
# define MMAP_PIXEL_SIZE 128

/* src/geometry/movement.c */
void	move_forward(t_cube *cube);
void	move_backward(t_cube *cube);
void	move_left(t_cube *cube);
void	move_right(t_cube *cube);

/* cast_floor.c */
void	cast_floor(t_cube *cube, int y);
void	render_game_over(t_cube *cube);
void	render_win_screen(t_cube *cube);

/* src/geometry/raycasting.c */
void	setup_dda_params(t_cube *cube, t_ray *ray);
void	perform_dda(t_cube *cube, t_ray *ray);
void	update_texts_pixels(t_cube *cube, t_ray *ray, int x);
void	raycast_bonus(t_cube *cube, t_ray *ray, int width);

/* src/sprites.c */
void	cast_sprites(t_cube *cube, double *z_buffer);
void	move_enemy(t_sprite_info *s_i, double *enemy_x, double *enemy_y);
void	sort_sprites(t_sprite *sprite, t_cube *cube);
void	draw_door(t_cube *cube, t_ray *ray, int x);
void	set_sprite_text(t_sprite *s, t_cube *c, int i);

/* src/geometry/rays.c */
void	init_ray(t_ray *ray);
void	setup_ray_params(t_cube *cube, t_ray *ray, int x);
void	calculate_line_height(t_cube *cube, t_ray *ray);
int		get_texture_index(t_ray *ray);
void	ray_calculations(t_cube *cube, t_ray *ray, int x);

/* src/geometry/render_main.c */
int		render_cube(t_cube *cube);
int		render(t_cube *cube);

/* src/geometry/render_minimap.c */
void	free_tab(void **tab);
void	init_img_clean(t_img *img);
void	init_img(t_cube *cube, t_img *image, int width, int height);
void	mm_set_image_pixel(t_img *image, int x, int y, int color);
void	set_minimap_tile_pixels(t_minimap *minimap, int x, int y, int color);
void	draw_minimap_tile(t_minimap *minimap, int x, int y);
void	set_minimap_border_image_pixels(t_minimap *minimap, int color);
void	draw_minimap(t_minimap *minimap);
void	render_minimap_image(t_cube *cube, t_minimap *minimap);
int		get_mmap_offset(t_minimap *minimap, int map_dimension, int player_pos);
char	*add_minimap_line(t_cube *d, t_minimap *m, int y, char **map);
char	**generate_minimap(t_cube *cube, t_minimap *minimap, char **map);
char	get_minimap_character(t_cube *d, t_minimap *m, char **map);

/* /src/mini_map/square_minimap.c */
char	**square_map(t_minimap *minimap, char **map);

/* /src/mini_map/square_minimap_utils.c */
int		find_longest_line(char **map);
int		calculate_map_lines(char **map);

void	render_minimap(t_cube *cube);
void	update_player_position(t_cube *cube);

/* src/geometry/render.c */
void	allocate_text_pixels(t_cube *cube);
void	set_image_pixel(t_img *img, int i[2], int color);
void	set_frame_image_pixel(t_cube *cube, t_img *img, int i[2]);
void	render_frame(t_cube *cube);

/* src/geometry/rotation.c */
void	rotate_left(t_cube *cube);
void	rotate_right(t_cube *cube);

/* src/geometry/set_cam_dir.c */
void	north(t_vec *front, t_vec *cam);
void	south(t_vec *front, t_vec *cam);
void	east(t_vec *front, t_vec *cam);
void	west(t_vec *front, t_vec *cam);
void	set_fr_cam_v(char player, t_vec *front, t_vec *cam);

/* src/geometry/vector_utils.c */
float	vec_to_ang(t_vec vec);
double	ang_to_rad(double ang);
t_vec	get_vunit(t_point p1, t_point p2);
t_vec	get_cam_vec(t_vec front, float fov);
double	get_front_length(t_cube *cube);

/* src/geometry/vector_utils2.c */
t_vec	rotate_vec(t_vec vec, float ang);
t_vec	find_casting_vec(t_cube *cube, int x);
t_vec	normalize_vec(t_vec vec);

/* src/mlx_functions/cleanup.c */
void	ft_strdel(char **s);
void	free_textures(t_cube *cube);
void	free_2darray(void **array);
void	destroy_screen(t_mlx *screen);

/* src/mlx_functions/cleanup2.c */
void	destroy_wall_textures(t_textures *wall_textures);
int		cleanup(t_cube *cube, int exit_code);
void	exit_program(t_cube *cube, int exit_code, char *message);

/* src/mlx_functions/hooking.c */
int		close_window(t_cube *cube);
bool	hooking(t_cube *cube);

/* src/mlx_functions/keyhooks.c */
void	handle_special_keys(int key, t_cube *cube);
int		key_press(int key, void *param);
int		key_release(int key, void *param);
int		keys_execute(t_cube *cube);

/* src/mlx_functions/keyhooks2.c */
void	show_hide_minimap(t_cube *cube);

/* src/mlx_functions/mouse_events.c */
int		mouse_release(int button, int x, int y, void *param);
// int		mouse_press(int button, int x, int y, void *param);
int		mouse_press(int key, void *param);
int		ft_mouse(t_cube *cube);

/* src/mlx_functions/resize_window.c */
void	resize_window(t_cube *cub, int flag);

/* src/parcer/floodfill.c */
void	initialize_player(t_cube *c, int i);
void	parse_player(t_cube *c);
void	check_walls(t_cube *cube);

/* src/parcer/gnl.c */
char	*get_next_line(int fd);

/* src/parcer/init.c */
void	init_cube(t_cube *cube);
void	set_screen_dimensions(t_cube *cube, Screen *s);
void	init_window(t_cube *cube);

/* src/parcer/parse_colors.c */
int		parse_color_code(char *line, int *color);

/* src/parcer/parse_file.c */
void	parse_file(char *map_path, char ***map_file, t_cube *cube);

/* src/parcer/parse_info.c */
void	load_texture(t_text_info *text_info);
void	parse_textures(char *trimmed_line, t_cube *cube);

/* src/parcer/parse_info2.c */
void	parse_floor_color(char *trimmed_line, t_cube *cube);
void	parse_ceiling_color(char *trimmed_line, t_cube *cube);
void	parse_map_lines(char *line, char **buffer, t_cube *cube);

/* src/parcer/parse_map.c */
void	parse_textures_files(t_cube *cube);
void	parse_map(char **map_file, t_cube *cube);

/* src/parcer/parse_utils.c */
void	multiple_error(int player_dir, int info[3]);
bool	is_valid_char(char c);
int		is_valid_line(char *line, t_cube *cube);
void	read_file(char *map_path, int *fd, t_cube *cube);
bool	line_has_walls(char *line);

/* src/parcer/positioning_elements.c */
int		is_player(char *line);
int		is_key(char *line);
int		is_enemy(char *line);
int		is_door(char *line);

/* src/parcer/print_map_info.c */
void	print_map_info(t_cube *cube);

/* src/urils/utils.c */
void	*ft_realloc(void *ptr, size_t size);
char	*ft_strncpy(char *dest, const char *src, size_t n);
int		ft_isspace(int c);
char	*trim_whitespace(const char *str);
char	*custom_strdup(const char *src);

/* src/main.c */
int		window_close(t_cube *cube);
void	check_args(int argc, char *argv[]);
void	parse(char *map_path, t_cube *cube);

#endif