/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:22:27 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 15:02:58 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_wall_textures(t_textures *wall_textures)
{
	int	i;

	if (!wall_textures)
		return ;
	i = NO;
	while (i <= EA)
	{
		if (wall_textures->textures[i])
			free(wall_textures->textures[i]);
		i++;
	}
}

int	cleanup(t_cube *cube, int exit_code)
{
	free_textures(cube);
	free_2darray((void **)cube->map.map);
	if (cube->map.map_file)
		free_2darray((void **)cube->map.map_file);
	destroy_wall_textures(&cube->wall_text);
	if (cube->screen.mlx)
		destroy_screen(&cube->screen);
	if (!cube)
		exit(exit_code);
	return (0);
}

void	exit_program(t_cube *cube, int exit_code, char *message)
{
	if (cube)
		cleanup(cube, exit_code);
	fprintf(stderr, "%s", message);
	exit(exit_code);
}
