/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 20:29:19 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 22:38:25 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*malloc(size_t size)
{
	void		*ret;

	pthread_mutex_lock(&g_alloc.mutex);
	ret = ft_malloc(size);
	VERBOSE_PRINT("malloc ( size=%lu ) : %p\n", size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	return (ret);
}

void			free(void *ptr)
{
	int			ret;
	size_t		size;

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
}

void			*calloc(size_t count, size_t size)
{
	void		*ret;

	pthread_mutex_lock(&g_alloc.mutex);
	ret = ft_malloc(count * size);
	if (ret)
		ft_bzero(ret, count * size);
	VERBOSE_PRINT("calloc ( count=%lu , size=%lu ) : ret\n",
		count, size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	return (ret);
}

void			*realloc(void *ptr, size_t size)
{
	void		*ret;
	size_t		freed_size;

	pthread_mutex_lock(&g_alloc.mutex);
	ret = ft_malloc(size);
	if (ret && ptr)
		ft_memcpy(ret, ptr, size);
	ft_free(ptr, &freed_size);
	VERBOSE_PRINT("realloc ( ptr=%p , size=%lu ) : ret\n", ptr, size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	return (ret);
}
