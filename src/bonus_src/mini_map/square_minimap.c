/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:55:16 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 14:00:13 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**allocate_map(int map_lines, int longest_line)
{
	int		i;
	char	**new_map;

	i = 0;
	new_map = ft_calloc(sizeof(char **), (map_lines + 1));
	while (i < map_lines)
	{
		new_map[i] = ft_calloc(sizeof(char *), (longest_line + 1));
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

static void	copy_map(char **new_map, char **map, int num_l, int longest_l)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL && i < num_l)
	{
		j = 0;
		while (map[i][j] != '\0' && j < longest_l)
		{
			new_map[i][j] = map[i][j];
			j++;
		}
		while (j < longest_l)
		{
			new_map[i][j] = '0';
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
}

static void	fill_map(char **new_map, int start_line, int longest_line)
{
	int	i;
	int	j;

	i = start_line;
	while (new_map[i] != NULL)
	{
		j = 0;
		while (j < longest_line)
		{
			new_map[i][j] = '0';
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
}

static char	**allocate_and_copy_map(int map_lines, int longest_l, char **map)
{
	char	**new_map;

	new_map = allocate_map(map_lines, longest_l);
	copy_map(new_map, map, map_lines, longest_l);
	fill_map(new_map, map_lines, longest_l);
	return (new_map);
}

char	**square_map(t_minimap *minimap, char **map)
{
	char	**new_map;

	minimap->map_lines = calculate_map_lines(map);
	if (minimap->map_lines < 8)
		minimap->map_lines = 8;
	minimap->longest_line = find_longest_line(map);
	if (minimap->longest_line < 8)
		minimap->longest_line = 8;
	new_map = allocate_and_copy_map(minimap->map_lines,
			minimap->longest_line, map);
	return (new_map);
}
