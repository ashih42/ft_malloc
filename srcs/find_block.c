/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 08:23:33 by ashih             #+#    #+#             */
/*   Updated: 2018/08/16 08:23:56 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		find_block_at_zone(void *ptr, t_zone **head, t_block **b,
	t_zone **z)
{
	FREE_ARGS;
	while (zone)
	{
		if ((void *)zone < ptr && ptr < zone->end)
		{
			prev = NULL;
			block = (void *)zone + sizeof(t_zone);
			while (block)
			{
				check_checksum(block);
				if ((void *)block + sizeof(t_block) == ptr)
				{
					*z = zone;
					*b = block;
					return (1);
				}
				prev = block;
				block = block->next;
			}
		}
		prev_zone = zone;
		zone = zone->next;
	}
	return (0);
}

int				find_block(void *ptr, t_block **b, t_zone **z)
{
	if (!ptr)
		return (0);
	else if (find_block_at_zone(ptr, &g_alloc.zone[TINY], b, z) ||
		find_block_at_zone(ptr, &g_alloc.zone[SMALL], b, z) ||
		find_block_at_zone(ptr, &g_alloc.zone[LARGE], b, z))
		return (1);
	else
		return (0);
}
