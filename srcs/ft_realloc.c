/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 01:34:11 by ashih             #+#    #+#             */
/*   Updated: 2018/08/16 21:17:32 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void		shrink_block(size_t size, t_block *block, t_zone *zone)
{
	block->size = size;
	block->checksum = (size_t)block + block->size;
	init_next_block(zone, block);
}

void			*ft_realloc(void *ptr, size_t size)
{
	void		*ret;
	t_block		*block;
	t_zone		*zone;
	size_t		old_size;

	ret = NULL;
	if (!ptr)
		ret = ft_malloc(size);
	else if (find_block_zone(ptr, &block, &zone))
	{
		if (size == 0)
			ft_free(ptr, &old_size);
		else if (size <= block->size)
		{
			shrink_block(size, block, zone);
			ret = ptr;
		}
		else if ((ret = ft_malloc(size)))
		{
			ft_memcpy(ret, ptr, MIN(block->size, size));
			ft_free(ptr, &old_size);
		}
	}
	return (ret);
}
