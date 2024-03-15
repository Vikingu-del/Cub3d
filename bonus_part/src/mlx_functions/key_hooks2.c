/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:17:43 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/26 15:12:08 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_hide_minimap(t_cube *cube)
{
	if (cube->minimap_data.show)
		cube->minimap_data.show = 0;
	else
		cube->minimap_data.show = 1;
}
