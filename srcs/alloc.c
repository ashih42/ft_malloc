/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 20:29:19 by ashih             #+#    #+#             */
/*   Updated: 2018/08/12 00:31:00 by ashih            ###   ########.fr       */
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

		ft_printf("malloc START: size = %lu\n", size);
	
	pthread_mutex_lock(&g_alloc.mutex);
	ret = ft_malloc(size);
	VERBOSE_PRINT("malloc ( size=%lu ) : %p\n", size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;

		// debug_all_zones(g_alloc.zone[1]);
		ft_printf(" malloc END\n");

	return (ret);
}

void			free(void *ptr)
{
	int			ret;
	size_t		size;

		ft_printf("free START\n");
		// debug_all_zones(g_alloc.zone[1]);

	pthread_mutex_lock(&g_alloc.mutex);
	VERBOSE_PRINT("free ( ptr=%p )", ptr);
	ret = ft_free(ptr, &size);
	if (ret == 1)
	{
		VERBOSE_PRINT(" Success! ( Released %lu bytes )\n", size);
	}
	else
	{
		VERBOSE_PRINT(" Fail!\n");
	}
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
	
		ft_printf(" free END\n");
}

// void			*calloc(size_t count, size_t size)
// {
// 	void		*ret;

// 		ft_printf("calloc START\n");

// 	pthread_mutex_lock(&g_alloc.mutex);
// 	ret = ft_malloc(count * size);
// 	if (ret)
// 		ft_bzero(ret, count * size);
// 	VERBOSE_PRINT("calloc ( count=%lu , size=%lu ) : %p\n",
// 		count, size, ret);
// 	pthread_mutex_unlock(&g_alloc.mutex);
// 	VIS_DELAY;

// 		ft_printf("calloc END\n");
	
// 	return (ret);
// }




void			*realloc(void *ptr, size_t size)
{
	int			find_success;
	void		*ret;
	size_t		ptr_size;

		ft_printf("realloc START\n");

	pthread_mutex_lock(&g_alloc.mutex);
	ret = ft_malloc(size);
	find_success = ft_find_size(ptr, &ptr_size);
	if (ret && ptr && find_success)
		ft_memcpy(ret, ptr, MIN(ptr_size, size));
	ft_free(ptr, &ptr_size);
	VERBOSE_PRINT("realloc ( ptr=%p , size=%lu ) : %p\n", ptr, size, ret);
	pthread_mutex_unlock(&g_alloc.mutex);
	VIS_DELAY;
		
		ft_printf("realloc END\n");
	return (ret);
}
