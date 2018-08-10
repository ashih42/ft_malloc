/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 20:34:55 by ashih             #+#    #+#             */
/*   Updated: 2018/08/10 05:57:01 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
** Defragment (merge adjacent FREE blocks)
** Merge curr with next, and curr with prev, if all are marked FREE
*/

//static void		merge(t_block *prev, t_block *curr)
static void		merge(t_block *prev, t_block *curr, t_zone *zone)
{
	curr->free = 1;
	if (curr->next && curr->next->free)
	{
		curr->size += sizeof(t_block) + curr->next->size;
		curr->next = curr->next->next;
		
		if (curr->next != NULL && (void *)curr->next >= zone->end) ft_printf("merge() FUCK 1\n");
	}
	if (prev && prev->free)
	{
		prev->size += sizeof(t_block) + curr->size;
		prev->next = curr->next;

		if (prev->next != NULL && (void *)prev->next >= zone->end) ft_printf("merge() FUCK 2\n");
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

static int		free_at_zone(void *ptr, t_zone **head, size_t *size)
{
	FREE_ARGS;
	while (zone)
	{
		debug_zone(zone);


		if ((void *)zone < ptr && ptr < zone->end)
		{
			prev = NULL;
			block = (void *)zone + sizeof(t_zone);
			while (block)
			{
				if ((void *)block + sizeof(t_block) == ptr && !block->free)
				{
					*size = block->size;
					merge(prev, block, zone);
					release_zone(head, zone, prev_zone);


//					debug_zone(zone);		// DEBUG
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

static int		free_at_large_zone(void *ptr, t_zone **head, size_t *size)
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
			break ;
		prev = zone;
		zone = zone->next;
	}
	if (!zone)
		return (0);
	*size = block->size;
	release_zone(head, zone, prev);
	return (1);
}

/*
** Return 1 if ptr is found and freed successfully
** Return 0 if ptr is not found
** Return -1 if ptr is NULL
*/

int				ft_free(void *ptr, size_t *size)
{
	if (!ptr)
		return (-1);
	else if (free_at_zone(ptr, &g_alloc.zone[TINY], size) ||
		free_at_zone(ptr, &g_alloc.zone[SMALL], size) ||
		free_at_large_zone(ptr, &g_alloc.zone[LARGE], size))
		return (1);
	else
		return (0);
}
