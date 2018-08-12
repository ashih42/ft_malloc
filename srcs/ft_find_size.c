/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 21:52:58 by ashih             #+#    #+#             */
/*   Updated: 2018/08/11 21:56:17 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		find_size_at_zone(void *ptr, t_zone **head, size_t *size)
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
					*size = block->size;
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

int				ft_find_size(void *ptr, size_t *size)
{
	if (!ptr)
		return (0);
	else if (find_size_at_zone(ptr, &g_alloc.zone[TINY], size) ||
		find_size_at_zone(ptr, &g_alloc.zone[SMALL], size) ||
		find_size_at_zone(ptr, &g_alloc.zone[LARGE], size))
		return (1);
	else
		return (0);
}
