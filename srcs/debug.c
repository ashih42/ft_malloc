/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 16:32:35 by ashih             #+#    #+#             */
/*   Updated: 2018/08/11 22:08:23 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			check_checksum(t_block *block)
{
	if (block->checksum != (size_t)block)
	{
		ft_printf("\t{red}FAILED CHECKSUM! ABORT!{reset}\n");
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
	if (block != (void *)block->checksum)
	{
		ft_printf("\t\tFAILED CHECKSUM! CORRECTING CHECKSUM NOW...\n");
		block->checksum = (size_t)block;
	}
}

void			debug_zone(t_zone *zone)
{
	t_block		*block;

	ft_printf("DEBUG_ZONE()\n");
	block = (void *)zone + sizeof(t_zone);
	while (block)
	{
		debug_block(block, zone);
		block = block->next;
	}
}

void			debug_all_zones(t_zone *zone)
{
	ft_printf("DEBUG_ALL_ZONES()\n");
	while (zone)
	{
		debug_zone(zone);
		zone = zone->next;
	}
}
