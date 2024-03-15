/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:35:25 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/22 16:49:17 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map_info(t_cube *cube)
{
	int	j;

	j = -1;
	printf("\t\tThe cube info is:\n");
	printf("\n\n\tThe map structure is:\n");
	while (cube->map.map[++j] != 0)
		printf("%s\n", cube->map.map[j]);
	j = -1;
	printf("\n\n\tThe map texture are is:\n");
	while (++j < cube->map.num_textures)
		printf("%s\n", cube->map.texture[j]);
	printf("\n\nThe floor colors are:\n");
	j = -1;
	while (++j < 3)
		printf("%d ", cube->map.floor_col[j]);
	j = -1;
	printf("\n\nThe ceiling colors are:\n");
	while (++j < 3)
		printf("%d ", cube->map.ceiling_col[j]);
	printf("\n\nPlayer's data are:\n");
	printf("player's x position: %f\n", cube->player.m_pos.x);
	printf("player's y position: %f\n", cube->player.m_pos.y);
	printf("\n\nmap_height: %d\n", cube->map.map_height);
	printf("\nmap_width: %d\n", cube->map.map_width);
}
