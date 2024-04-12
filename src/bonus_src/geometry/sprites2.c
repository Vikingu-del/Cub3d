/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:18:28 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 17:21:54 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_sprite *sprite, t_cube *cube)
{
	int		i;
	int		temp_order;
	double	temp_distance;

	i = -1;
	while (++i < DOOR)
	{
		sprite->sprite_order[i] = i;
		sprite->sprite_dist[i] = ((cube->player.pos[X] - \
		cube->sprite.sprite_text[i].text_pos[X]) * (cube->player.pos[X] - \
		cube->sprite.sprite_text[i].text_pos[X]) + (cube->player.pos[Y] - \
		cube->sprite.sprite_text[i].text_pos[Y]) * (cube->player.pos[Y] - \
		cube->sprite.sprite_text[i].text_pos[Y]));
	}
	if (sprite->sprite_dist[ENEMY] > sprite->sprite_dist[KEY])
		return ;
	else
	{
		temp_order = sprite->sprite_order[ENEMY];
		sprite->sprite_order[ENEMY] = sprite->sprite_order[KEY];
		sprite->sprite_order[KEY] = temp_order;
		temp_distance = sprite->sprite_dist[ENEMY];
		sprite->sprite_dist[ENEMY] = sprite->sprite_dist[KEY];
		sprite->sprite_dist[KEY] = temp_distance;
	}
}

static void	set_sprite_text_2(t_sprite *s, t_cube *c, int i)
{
	s->sprite_text[i].text_pos[X] = s->sprite_text[i].text_point[X] \
	- c->player.pos[X];
	s->sprite_text[i].text_pos[Y] = s->sprite_text[i].text_point[Y] \
	- c->player.pos[Y];
	s->sprite_text[i].inv_det = 1.0 / (c->player.cam.dir[X] * \
	c->player.front.dir[Y] - c->player.front.dir[X] * c->player.cam.dir[Y]);
	s->sprite_text[i].transform[X] = s->sprite_text[i].inv_det * \
	(c->player.front.dir[Y] * s->sprite_text[i].text_pos[X] - \
	c->player.front.dir[X] * s->sprite_text[i].text_pos[Y]);
	s->sprite_text[i].transform[Y] = s->sprite_text[i].inv_det * \
	(-c->player.cam.dir[Y] * s->sprite_text[i].text_pos[X] + \
	c->player.cam.dir[X] * s->sprite_text[i].text_pos[Y]);
	s->sprite_text[i].screen_x = (int)((c->screen.width / 2) * \
	(1 + s->sprite_text[i].transform[X] / s->sprite_text[i].transform[Y]));
	s->sprite_text[i].h = abs((int)(c->screen.height / \
	(s->sprite_text[i].transform[Y])));
	s->sprite_text[i].start[Y] = -s->sprite_text[i].h / 2 + \
	c->screen.height / 2;
}

void	set_sprite_text(t_sprite *s, t_cube *c, int i)
{
	set_sprite_text_2(s, c, i);
	if (s->sprite_text[i].start[Y] < 0)
		s->sprite_text[i].start[Y] = 0;
	s->sprite_text[i].end[Y] = s->sprite_text[i].h / 2 + \
	c->screen.height / 2;
	if (s->sprite_text[i].end[Y] >= c->screen.height)
		s->sprite_text[i].end[Y] = c->screen.height - 1;
	s->sprite_text[i].w = abs((int)(c->screen.height / \
	(s->sprite_text[i].transform[Y])));
	s->sprite_text[i].start[X] = -s->sprite_text[i].w / 2 + \
	s->sprite_text[i].screen_x;
	if (s->sprite_text[i].start[X] < 0)
		s->sprite_text[i].start[X] = 0;
	s->sprite_text[i].end[X] = s->sprite_text[i].w / 2 + \
	s->sprite_text[i].screen_x;
	if (s->sprite_text[i].end[X] >= c->screen.width)
		s->sprite_text[i].end[X] = c->screen.width - 1;
}
