/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:01:36 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 17:01:57 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_text_dir(char *text, int i)
{
	if ((i == NO && !ft_strncmp(text, "NO ", 3))
		|| (i == SO && !ft_strncmp(text, "SO ", 3))
		|| (i == EA && !ft_strncmp(text, "EA ", 3))
		|| (i == WE && !ft_strncmp(text, "WE ", 3)))
		return (0);
	else
		return (-1);
}
