/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 20:34:55 by ashih             #+#    #+#             */
/*   Updated: 2018/08/16 21:08:36 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** Defragment (merge adjacent FREE blocks)
** Merge curr with next, and curr with prev, if all are marked FREE
*/

static void		merge(t_block *prev, t_block *curr)
{
	if (curr->next && curr->next->free)
	{
		curr->size += sizeof(t_block) + curr->next->size;
		curr->next = curr->next->next;
		curr->checksum = (size_t)curr + curr->size;
	}
	if (prev && prev->free)
	{
		prev->size += sizeof(t_block) + curr->size;
		prev->next = curr->next;
		prev->checksum = (size_t)prev + prev->size;
	}
}

static void		release_zone(t_zone **head, t_zone *zone, t_zone *prev)
{
	t_block		*block;
	char		*str;
	size_t		size;

	block = (void *)zone + sizeof(t_zone);
	while (block)
	{
		if (block->free == 0)
			return ;
		block = block->next;
	}
	if (prev)
		prev->next = zone->next;
	else
		*head = zone->next;
	size = (size_t)(zone->end - (void *)zone);
	str = "LARGE";
	str = (size == (size_t)SMALL_ZONE_SIZE) ? "TINY" : str;
	str = (size == (size_t)LARGE_ZONE_SIZE) ? "SMALL" : str;
	VERBOSE_PRINT("  {blue}munmap : %s zone at %p ( size=%lu ){reset}\n",
		str, zone, size);
	munmap(zone, size);
}

static int		free_block_chain(t_block *block, void *ptr, size_t *size)
{
	t_block		*prev;

	prev = NULL;
	while (block)
	{
		if ((void *)block + sizeof(t_block) == ptr && !block->free)
		{
			block->free = 1;
			*size = block->size;
			merge(prev, block);
			return (1);
		}
		prev = block;
		block = block->next;
	}
	return (0);
}

static int		free_at_zone(t_zone **head, void *ptr, size_t *size)
{
	t_zone		*zone;
	t_zone		*prev;
	t_block		*block;

	zone = *head;
	prev = NULL;
	while (zone)
	{
		if ((void *)zone < ptr && ptr < zone->end)
		{
			block = (void *)zone + sizeof(t_zone);
			if (free_block_chain(block, ptr, size))
			{
				release_zone(head, zone, prev);
				return (1);
			}
		}
		prev = zone;
		zone = zone->next;
	}
	return (0);
}

/*
** Return 1 if ptr is found and freed successfully
** Return 0 if ptr is not found
*/

int				ft_free(void *ptr, size_t *size)
{
	if (!ptr)
		return (0);
	else if (free_at_zone(&g_alloc.zone[TINY], ptr, size) ||
		free_at_zone(&g_alloc.zone[SMALL], ptr, size) ||
		free_at_zone(&g_alloc.zone[LARGE], ptr, size))
		return (1);
	else
		return (0);
}
