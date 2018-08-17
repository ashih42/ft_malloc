/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 08:23:33 by ashih             #+#    #+#             */
/*   Updated: 2018/08/16 21:08:08 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		find_at_zone(t_zone *zone, void *ptr, t_block **b,
	t_zone **z)
{
	t_block		*block;

	while (zone)
	{
		if ((void *)zone < ptr && ptr < zone->end)
		{
			block = (void *)zone + sizeof(t_zone);
			while (block)
			{
				if ((void *)block + sizeof(t_block) == ptr)
				{
					*b = block;
					*z = zone;
					return (1);
				}
				block = block->next;
			}
		}
		zone = zone->next;
	}
	return (0);
}

int				find_block_zone(void *ptr, t_block **b, t_zone **z)
{
	if (!ptr)
		return (0);
	else if (find_at_zone(g_alloc.zone[TINY], ptr, b, z) ||
		find_at_zone(g_alloc.zone[SMALL], ptr, b, z) ||
		find_at_zone(g_alloc.zone[LARGE], ptr, b, z))
		return (1);
	else
		return (0);
}
