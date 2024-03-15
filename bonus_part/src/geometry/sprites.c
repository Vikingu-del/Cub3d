/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:21:32 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 17:20:39 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_sprite_info(t_sprite_info *s_i, t_cube *c, double *z_buf)
{
	s_i->m_h = c->map.map_height;
	s_i->m_w = c->map.map_width;
	s_i->m = c->map.map;
	s_i->c = c;
	s_i->z_b = z_buf;
}

static void	process_sprite_2(t_sprite_info *s_i, int *i, int *tex, int stripe)
{
	i[Y] = s_i->sprite_text.start[Y];
	while (i[Y] < s_i->sprite_text.end[Y])
	{
		s_i->sprite_text.d = (i[Y]) * 256 - s_i->c->screen.height * \
		128 + s_i->sprite_text.h * 128;
		tex[Y] = ((s_i->sprite_text.d * TEXT_SIZE) / \
		s_i->sprite_text.h) / 256;
		s_i->sprite_text.color = s_i->sprite_text.pixels[TEXT_SIZE \
		* tex[Y] + tex[X]];
		if ((s_i->sprite_text.color & 0x00FFFFFF) != 0)
			s_i->c->text_pixels[i[Y]][stripe] = s_i->sprite_text.color;
		i[Y]++;
	}
}

void	process_sprite(t_sprite_info *s_i, int *i)
{
	int	stripe;
	int	tex[2];

	if (i[X] == KEY && s_i->c->key_status == 1)
		return ;
	set_sprite_text(&s_i->c->sprite, s_i->c, \
	s_i->c->sprite.sprite_order[i[X]]);
	s_i->sprite_text = \
	s_i->c->sprite.sprite_text[s_i->c->sprite.sprite_order[i[X]]];
	stripe = s_i->sprite_text.start[X];
	while (stripe < s_i->sprite_text.end[X])
	{
		tex[X] = (int)(256 * (stripe - (-s_i->sprite_text.w / 2 \
		+ s_i->sprite_text.screen_x)) * TEXT_SIZE / \
		s_i->sprite_text.w) / 256;
		if (s_i->sprite_text.transform[Y] > 0 && stripe > 0 && stripe \
		< s_i->c->screen.width && s_i->sprite_text.transform[Y] \
		< s_i->z_b[stripe])
			process_sprite_2(s_i, i, tex, stripe);
		stripe++;
	}
}

void	cast_sprites(t_cube *c, double *z_buffer)
{
	int				i[2];
	t_sprite_info	s_i;

	init_sprite_info(&s_i, c, z_buffer);
	i[X] = -1;
	move_enemy(&s_i, &c->sprite.sprite_text[ENEMY].text_point[X], \
	&c->sprite.sprite_text[ENEMY].text_point[Y]);
	sort_sprites(&c->sprite, c);
	while (++i[X] < 2)
		process_sprite(&s_i, i);
}
