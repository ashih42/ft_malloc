/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 20:29:19 by ashih             #+#    #+#             */
/*   Updated: 2018/08/16 20:30:46 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc			g_alloc =
{
	{NULL, NULL, NULL}, PTHREAD_MUTEX_INITIALIZER, NULL,
	NULL, 0, 0, 0, 0, 0, NULL,
	0, 0, 0,
	"#version 330 core \n"
	"layout (location = 0) in vec2 aPos; \n"
	"layout (location = 1) in vec2 aTexCoord; \n"
	"out vec2 TexCoord; \n"
	"void main() \n"
	"{ \n"
	"	gl_Position = vec4(aPos.x, -aPos.y, 0.0, 1.0); \n"
	"	TexCoord = aTexCoord; \n"
	"} \n",
	"#version 330 core \n"
	"out vec4 FragColor; \n"
	"in vec2 TexCoord; \n"
	"uniform sampler2D frameTex; \n"
	"void main() \n"
	"{ \n"
	"	FragColor = texture(frameTex, TexCoord); \n"
	"	FragColor = FragColor.zyxw; \n"
	"} \n"
};

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
	size_t		size;

	pthread_mutex_lock(&g_alloc.mutex);
	VERBOSE_PRINT("free ( ptr=%p )", ptr);
	if (!ptr)
	{
		VERBOSE_PRINT(" No operation!\n");
	}
	else if (ft_free(ptr, &size))
	{
		VERBOSE_PRINT(" Success! ( Released %lu bytes )\n", size);
	}
	else
	{
		VERBOSE_PRINT(" {red}Error: ptr was not allocated!{reset}\n");
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
	VERBOSE_PRINT("calloc ( count=%lu , size=%lu ) : %p\n",
		count, size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	return (ret);
}

void			*realloc(void *ptr, size_t size)
{
	R_ARGS;
	pthread_mutex_lock(&g_alloc.mutex);
	if (!ptr)
		ret = ft_malloc(size);
	else if (find_block(ptr, &block, &zone))
	{
		if (size == 0)
			ft_free(ptr, &ptr_size);
		else if (size <= block->size)
		{
			shrink_block(size, block, zone);
			ret = ptr;
		}
		else if ((ret = ft_malloc(size)))
		{
			ft_memcpy(ret, ptr, MIN(block->size, size));
			ft_free(ptr, &ptr_size);
		}
	}
	VERBOSE_PRINT("realloc ( ptr=%p , size=%lu ) : %p\n", ptr, size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	return (ret);
}
