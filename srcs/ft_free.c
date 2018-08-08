/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 20:34:55 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 05:14:57 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** Defragment (merge adjacent FREE blocks)
** Merge curr with next, and curr with prev, if all are marked FREE
*/
static void		merge(t_block *prev, t_block *curr)
{
	curr->free = 1;

	// merge curr and next
	if (curr->next && curr->next->free)
	{
		curr->size += sizeof(t_block) + curr->next->size;
		curr->next = curr->next->next;
	}

	// merge prev and curr
	if (prev && prev->free)
	{
		prev->size += sizeof(t_block) + curr->size;
		prev->next = curr->next;
	}
}

static void		release_zone(t_zone **head, t_zone *zone, t_zone *prev)
{
	t_block		*block;

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
	munmap(zone, (size_t)(zone->end - (void *)zone));
}

static int		free_at_zone(void *ptr, t_zone **head)
{

	t_zone		*zone;
	t_zone		*prev_zone;
	t_block		*prev;
	t_block		*block;

	zone = *head;
	prev_zone = NULL;
	while(zone)
	{
		prev = NULL;
		block = (void *)zone + sizeof(t_zone);
		while (block)
		{
			if ((void *)block + sizeof(t_block) == ptr && !block->free)
			{
				merge(prev, block);
				release_zone(head, zone, prev_zone);
				return (1);
			}
			prev = block;
			block = block->next;
		}
		prev_zone = zone;
		zone = zone->next;
	}
	return (0);
}

static int		free_at_large_zone(void *ptr, t_zone **head)
{
	t_zone		*zone;
	t_zone		*prev;
	t_block		*block;

	prev = NULL;
	zone = *head;
	while (zone)
	{
		block = (void *)zone + sizeof(t_zone);
		if ((void *)block + sizeof(t_block) == ptr)
			break;
		prev = zone;
		zone = zone->next;
	}
	if (!zone)
		return (0);

	release_zone(head, zone, prev);
	return (1);
}

void			ft_free(void *ptr)
{
	ft_printf("ft_free ( ptr=%p )", ptr);
	if (!ptr)
	{
		ft_printf("  (╯°□°）╯︵ ┻━┻\n");
		return;
	}
	pthread_mutex_lock(&g_alloc.mutex);
	if (free_at_zone(ptr, &g_alloc.zone[TINY]) ||
		free_at_zone(ptr, &g_alloc.zone[SMALL]) ||
		free_at_large_zone(ptr, &g_alloc.zone[LARGE]))
		ft_printf("  success!\n");
	else
		ft_printf("  fail!\n");
	pthread_mutex_unlock(&g_alloc.mutex);
	if (g_alloc.window)
		usleep(SLEEP_TIME);
}
