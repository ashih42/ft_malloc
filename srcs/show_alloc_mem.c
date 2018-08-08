/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 05:45:40 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 08:53:49 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			print_blocks(t_block *block, int ex_mode)
{
	int				j;

	j = 0;
	while (block)
	{
		ft_printf("    BLOCK %d: %p - %p : %lu bytes, free = %s\n", j++,
			(void *)block + sizeof(t_block),
			(void *)block + sizeof(t_block) + block->size,
			block->size, block->free ? "YES" : "NO");
		if (ex_mode && !block->free)
			hexdump(block);
		block = block->next;
	}
}

static void			print_zones(t_zone *zone, int zone_id, int ex_mode)
{
	int				i;

	i = 0;
	while (zone)
	{
		if (zone_id == TINY)
			ft_printf("{cheese}");
		else if (zone_id == SMALL)
			ft_printf("{burger}");
		else
			ft_printf("{pizza}");
		ft_printf(" ZONE %d : ( size = %lu bytes )\n", i++,
			(zone->end - (void *)zone));
		print_blocks((void *)zone + sizeof(t_zone), ex_mode);
		zone = zone->next;
	}
}

void				show_alloc_mem(void)
{
	pthread_mutex_lock(&g_alloc.mutex);
	ft_printf("{invert}TINY{reset} : %p\n", g_alloc.zone[TINY]);
	print_zones(g_alloc.zone[TINY], TINY, 0);
	ft_printf("{invert}SMALL{reset} : %p\n", g_alloc.zone[SMALL]);
	print_zones(g_alloc.zone[SMALL], SMALL, 0);
	ft_printf("{invert}LARGE{reset} : %p\n", g_alloc.zone[LARGE]);
	print_zones(g_alloc.zone[LARGE], LARGE, 0);
	pthread_mutex_unlock(&g_alloc.mutex);
}

void				show_alloc_mem_ex(void)
{
	pthread_mutex_lock(&g_alloc.mutex);
	ft_printf("{invert}TINY{reset} : %p\n", g_alloc.zone[TINY]);
	print_zones(g_alloc.zone[TINY], TINY, 1);
	ft_printf("{invert}SMALL{reset} : %p\n", g_alloc.zone[SMALL]);
	print_zones(g_alloc.zone[SMALL], SMALL, 1);
	ft_printf("{invert}LARGE{reset} : %p\n", g_alloc.zone[LARGE]);
	print_zones(g_alloc.zone[LARGE], LARGE, 1);
	pthread_mutex_unlock(&g_alloc.mutex);
}
