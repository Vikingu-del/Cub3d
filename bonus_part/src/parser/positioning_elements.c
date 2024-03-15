/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positioning_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:43:13 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 12:46:09 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_key(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] == '3')
			return (pos);
		pos++;
	}
	return (0);
}

int	is_door(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] == '2')
			return (pos);
		pos++;
	}
	return (0);
}

int	is_enemy(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] == '4')
			return (pos);
		pos++;
	}
	return (0);
}

int	is_player(char *line)
{
	int	pos;

	pos = 0;
	while (line[pos])
	{
		if (line[pos] == 'N' || line[pos] == 'S'
			|| line[pos] == 'E' || line[pos] == 'W')
			return (pos);
		pos++;
	}
	return (0);
}
