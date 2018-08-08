/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:19:48 by ashih             #+#    #+#             */
/*   Updated: 2018/08/07 22:22:58 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			print_blocks(t_block *block)
{
	int			j;

	j = 0;
	while (block)
	{
		ft_printf("    BLOCK %d: %p - %p : %lu bytes, free=%d, val=%d\n",
			j++,
			(void *)block + sizeof(t_block),
			(void *)block + sizeof(t_block) + block->size,
			block->size,
			block->free,
			*(int *)((void *)block + sizeof(t_block))
		);
		block = block->next;
	}
}




void			print_zones(t_zone *zone)
{
	// if (!getenv(ENV_BLOCKS))
	// 	return;

	int			i;

	i = 0;
	while (zone)
	{
		ft_printf("  ZONE %d:\n", i++);
		ft_printf("  zone size: %lu\n", (zone->end - (void *)zone));

		print_blocks((void *)zone + sizeof(t_zone));
		zone = zone->next;
	}
}

void			print_alloc(void)
{
	ft_printf("TINY:\n");
	print_zones(g_alloc.zone[TINY]);
	
	ft_printf("SMALL:\n");
	print_zones(g_alloc.zone[SMALL]);
	
	ft_printf("LARGE:\n");
	print_zones(g_alloc.zone[LARGE]);
	
	ft_printf("\n");
}
