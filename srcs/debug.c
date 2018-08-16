/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 16:32:35 by ashih             #+#    #+#             */
/*   Updated: 2018/08/16 08:25:39 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			check_checksum(t_block *block)
{
	if (block->checksum != (size_t)block + block->size)
	{
		ft_printf("{red}FAILED CHECKSUM! ABORT! (ノಠ益ಠ)ノ彡┻━┻{reset}\n");
		abort();
	}
}

void			debug_block(t_block *block, t_zone *zone)
{
	if (block == NULL)
	{
		ft_printf("block = NULL\n");
		return ;
	}
	ft_printf("DEBUG: block = %p, ptr = %p, free = %d, size = %d, next = %p, "
		"checksum = %p;\n\tzone = [%p, %p], is_in_range=%d\n",
		block, (void *)block + sizeof(t_block), block->free, block->size,
		block->next, (void *)block->checksum, zone, zone->end,
		((void *)zone < (void *)block && (void *)block < zone->end));
	if (block->checksum != (size_t)block + block->size)
	{
		ft_printf("\t\tFAILED CHECKSUM! CORRECTING CHECKSUM NOW...\n");
		block->checksum = (size_t)block + block->size;
	}
	(void)zone;
}

void			debug_zone_list(t_zone *zone)
{
	t_block		*block;

	while (zone)
	{
		block = (void *)zone + sizeof(t_zone);
		while (block)
		{
			check_checksum(block);
			block = block->next;
		}
		zone = zone->next;
	}
}

void			debug_all_zones(void)
{
	ft_printf("DEBUG_ALL_ZONES()...  ");
	debug_zone_list(g_alloc.zone[TINY]);
	debug_zone_list(g_alloc.zone[SMALL]);
	debug_zone_list(g_alloc.zone[LARGE]);
	ft_printf("OK\n");
}
