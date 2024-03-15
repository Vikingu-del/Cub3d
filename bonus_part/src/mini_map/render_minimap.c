/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:30:03 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 14:02:31 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_mmap_offset(t_minimap *minimap, int size, int p_pos)
{
	if (p_pos > minimap->view_dist && size - p_pos > (minimap->view_dist + 1))
		return (p_pos - minimap->view_dist);
	if (p_pos > minimap->view_dist && size - p_pos <= (minimap->view_dist + 1))
		return (size - minimap->size);
	return (0);
}

bool	is_valid_pos_wall_collision(t_cube *cube, double x, double y)
{
	if (cube->map.map[(int)y][(int)x] == '1'
		|| cube->map.map[(int)y][(int)x] == '2'
		|| cube->map.map[(int)(y + 0.1)][(int)(x + 0.1)] == '1'
		|| cube->map.map[(int)(y - 0.1)][(int)(x - 0.1)] == '1')
		return (false);
	return (true);
}

void	update_player_position(t_cube *cube)
{
	double	new_x;
	double	new_y;

	new_x = cube->player.pos[X] + cube->player.front.dir[X]
		* cube->player.player_speed * 2;
	new_y = cube->player.pos[Y] + cube->player.front.dir[Y]
		* cube->player.player_speed * 2;
	if (is_valid_pos_wall_collision(cube, new_x, new_y) == true)
	{
		cube->player.m_pos.x = new_x;
		cube->player.m_pos.y = new_y;
	}
}

void	calculate_minimap_offset(t_minimap *minimap, t_cube *cube)
{
	minimap->offset_x = get_mmap_offset(minimap, cube->map.map_width,
			(int)cube->player.pos[X]);
	minimap->offset_y = get_mmap_offset(minimap, cube->map.map_height,
			(int)cube->player.pos[Y]);
}

void	render_minimap(t_cube *cube)
{
	t_minimap	minimap;
	char		**new_map;

	minimap.map = NULL;
	cube->minimap_data = minimap;
	minimap.img = &cube->minimap;
	minimap.view_dist = 4;
	minimap.size = 2 * minimap.view_dist;
	minimap.tile_size = MMAP_PIXEL_SIZE / (2 * minimap.view_dist);
	minimap.key_status = cube->key_status;
	calculate_minimap_offset(&minimap, cube);
	update_player_position(cube);
	new_map = square_map(&minimap, cube->map.map);
	minimap.map = generate_minimap(cube, &minimap, new_map);
	if (!minimap.map)
		exit_program(cube, 1, "Error: minimap generation failed");
	render_minimap_image(cube, &minimap);
	free_tab((void **)new_map);
	free_tab((void **)minimap.map);
}
