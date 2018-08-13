/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 21:04:56 by ashih             #+#    #+#             */
/*   Updated: 2018/08/12 20:38:24 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** Case (1): block is the last block in this zone
** Case (2): block is NOT the last block in this zone
*/

static void		init_next_block(t_zone *zone, t_block *block)
{
	t_block		*next;

	next = (void *)block + sizeof(t_block) + block->size;
	if (!block->next && (void *)next + sizeof(t_block) < zone->end)
	{
		block->next = next;
		next->size = zone->end - ((void *)next + sizeof(t_block));
		next->free = 1;
		next->next = NULL;
		next->checksum = (size_t)next;
	}
	else if (block->next && (void *)next + sizeof(t_block) <
		(void *)block->next)
	{
		next->size = (void *)block->next - ((void *)next + sizeof(t_block));
		next->free = 1;
		next->next = block->next;
		next->checksum = (size_t)next;
		block->next = next;
	}
}

static void		*find_space(t_zone *zone, size_t size)
{
	t_block		*block;

	while (zone)
	{
		block = (void *)zone + sizeof(t_zone);
		while (block)
		{
			check_checksum(block);
			if (block->free && size <= block->size)
			{
				block->size = size;
				block->free = 0;
				block->checksum = (size_t)block;
				init_next_block(zone, block);
				return ((void *)block + sizeof(t_block));
			}
			block = block->next;
		}
		zone = zone->next;
	}
	return (NULL);
}

static void		*malloc_at_zone(size_t size, int zid)
{
	void		*ret;
	t_zone		*zone;

	ret = find_space(g_alloc.zone[zid], size);
	if (!ret)
	{
		if (zid == TINY)
			zone = add_zone(&g_alloc.zone[zid], new_zone(SMALL_ZONE_SIZE));
		else if (zid == SMALL)
			zone = add_zone(&g_alloc.zone[zid], new_zone(LARGE_ZONE_SIZE));
		else
			zone = add_zone(&g_alloc.zone[zid], new_zone(
				size + sizeof(t_block) + sizeof(t_zone)));
		if (!zone)
			return (NULL);
		ret = find_space(g_alloc.zone[zid], size);
	}
	return (ret);
}

void			*ft_malloc(size_t size)
{
	void		*ret;

	if (size == 0)
		ret = NULL;
	else if (size <= SMALL_SIZE_CUTOFF)
		ret = malloc_at_zone(size, TINY);
	else if (size <= LARGE_SIZE_CUTOFF)
		ret = malloc_at_zone(size, SMALL);
	else
		ret = malloc_at_zone(size, LARGE);
	return (ret);
}
