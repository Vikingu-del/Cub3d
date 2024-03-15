/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_minimap_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:43:51 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 13:58:11 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_longest_line(char **map)
{
	int	i;
	int	longest;

	i = 0;
	longest = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)longest)
			longest = ft_strlen(map[i]);
		i++;
	}
	return (longest + 1);
}

int	calculate_map_lines(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
