/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 20:29:19 by ashih             #+#    #+#             */
/*   Updated: 2018/08/10 00:05:29 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			debug_block(t_block *block, t_zone *zone)
{
	if (block == NULL)
	{
		ft_printf("block = NULL\n");
		return;
	}
	ft_printf("DEBUG: block = %p, ptr = %p, free = %d, size = %d, next = %p;\n\tzone = [%p, %p], is_in_range=%d\n",
		block, (void *)block + sizeof(t_block), block->free, block->size, block->next,
		zone, zone->end,
		((void *)zone < (void *)block && (void *)block < zone->end));
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

void			*malloc(size_t size)
{
	void		*ret;

	ft_printf("malloc START: size = %lu\n", size);
	pthread_mutex_lock(&g_alloc.mutex);
	//ft_printf(" calling ft_malloc()\n");
	ret = ft_malloc(size);
	//ft_printf(" returning from ft_malloc()\n");
	VERBOSE_PRINT("malloc ( size=%lu ) : %p\n", size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	ft_printf(" malloc END\n");
	return (ret);
}

void			free(void *ptr)
{
	int			ret;
	size_t		size;

	ft_printf("free START\n");
	pthread_mutex_lock(&g_alloc.mutex);
	VERBOSE_PRINT("free ( ptr=%p )", ptr);
	ret = ft_free(ptr, &size);
	if (ret == 1)
	{
		VERBOSE_PRINT(" Success! ( Released %lu bytes )\n", size);
	}
	else if (ret == 0)
	{
		VERBOSE_PRINT(" Fail!\n");
	}
	else
	{
		VERBOSE_PRINT(" (╯°□°）╯︵ ┻━┻\n");
	}
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	ft_printf(" free END\n");
}
/*
void			*calloc(size_t count, size_t size)
{
	void		*ret;

	ft_printf("calloc START\n");
	pthread_mutex_lock(&g_alloc.mutex);
	ret = ft_malloc(count * size);
	if (ret)
		ft_bzero(ret, count * size);
	VERBOSE_PRINT("calloc ( count=%lu , size=%lu ) : %p\n",
		count, size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	ft_printf("calloc END\n");
	return (ret);
}
*/
void			*realloc(void *ptr, size_t size)
{
	void		*ret;
	size_t		freed_size;

	ft_printf("realloc START\n");
	pthread_mutex_lock(&g_alloc.mutex);
	ret = ft_malloc(size);
	if (ret && ptr)
		ft_memcpy(ret, ptr, size);
	ft_free(ptr, &freed_size);
	VERBOSE_PRINT("realloc ( ptr=%p , size=%lu ) : %p\n", ptr, size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	ft_printf("realloc END\n");
	return (ret);
}
