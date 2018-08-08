/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:22:13 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 01:57:51 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			draw_block(t_block *block, t_zone *zone, int index)
{
	int			y_top;
	int			x_start;
	int			x_len;

	y_top = FRAME_MARGIN + (FRAME_MARGIN + FRAME_HEIGHT) * index;
	x_start = FRAME_MARGIN + (int)CHANGE(((size_t)block),
		((size_t)zone), ((size_t)zone->end), 0, (FRAME_WIDTH));
	draw_line_vert((t_vect2i){x_start, y_top}, FRAME_HEIGHT, 0x00FF00);
	if (block->free)
		return ;
	if (block->next)
		x_len = FRAME_MARGIN + (int)CHANGE(((size_t)block->next),((size_t)zone),
			((size_t)zone->end), 0, (FRAME_WIDTH)) - x_start;
	else
		x_len = FRAME_WIDTH - x_start;
	x_len = MAX(x_len, 1);
	draw_sq((t_vect2i){x_start, y_top}, (t_vect2i){x_len, FRAME_HEIGHT}, 0xFF0000);
}

void			draw_zone(t_zone *zone, int index)
{
	int			y_top;
	t_block		*block;

	if (!zone)
		return ;
	y_top = FRAME_MARGIN + (FRAME_MARGIN + FRAME_HEIGHT) * index;
	block = (void *)zone + sizeof(t_zone);
	while (block)
	{
		draw_block(block, zone, index);
		block = block->next;
	}
	draw_box((t_vect2i){FRAME_MARGIN, y_top}, (t_vect2i){FRAME_WIDTH, FRAME_HEIGHT}, 0xFFFFFF);
}


void		render(void)
{
	int		index;
	t_zone	*zone;

	index = 0;
	ft_bzero(g_alloc.frame, sizeof(int) * WIN_WIDTH * WIN_HEIGHT);
	zone = g_alloc.zone[TINY];

	while (zone && index < 3)
	{
		draw_zone(zone, index++);
		zone = zone->next;
	}

}
