/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 20:31:46 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 07:04:26 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** No boundary checking
** (x, y) MUST already be within valid range
*/

static void		draw_dot(int x, int y, int color)
{
	g_alloc.frame[x + y * WIN_WIDTH] = color;
}

static void		draw_line_horiz(t_vect2i pos, int len, int color)
{
	int			x;

	x = 0;
	while (x < len)
		draw_dot(pos.x + x++, pos.y, color);
}

void			draw_line_vert(t_vect2i pos, int len, int color)
{
	int			y;

	y = 0;
	while (y < len)
		draw_dot(pos.x, pos.y + y++, color);
}

/*
**  -----------------> x, width
** |
** |
** |
** V
** y, height
*/

void			draw_box(t_vect2i upper_left, t_vect2i dimen, int color)
{
	t_vect2i	upper_right;
	t_vect2i	bottom_left;

	upper_right.x = upper_left.x + dimen.x - 1;
	upper_right.y = upper_left.y;
	bottom_left.x = upper_left.x;
	bottom_left.y = upper_left.y + dimen.y - 1;
	draw_line_horiz(upper_left, dimen.x, color);
	draw_line_horiz(bottom_left, dimen.x, color);
	draw_line_vert(upper_right, dimen.y, color);
}

void			draw_sq(t_vect2i pos, t_vect2i dimen, int color)
{
	int			y;

	y = 0;
	while (y < dimen.y)
	{
		draw_line_horiz(pos, dimen.x, color);
		pos.y++;
		y++;
	}
}
