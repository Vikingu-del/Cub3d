/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:50:38 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/16 10:12:43 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "error.h"

void	ft_strdel(char **s)
{
	if (!s)
		return ;
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	*s = NULL;
}

void	free_textures(t_cube *cube)
{
	int	i;

	i = 0;
	while (i < cube->map.num_textures)
	{
		free(cube->map.texture[i]);
		i++;
	}
}

void	free_2darray(void **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
	array = NULL;
}

void	destroy_screen(t_mlx *screen)
{
	if (screen->img.img)
		mlx_destroy_image(screen->mlx, screen->img.img);
	if (screen->win)
		mlx_destroy_window(screen->mlx, screen->win);
}
