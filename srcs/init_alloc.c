/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:19:41 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 07:24:32 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc				g_alloc =
{
	{0, 0, 0}, PTHREAD_MUTEX_INITIALIZER, NULL,
	NULL, 0, 0, 0, 0, 0, NULL, 0
};

static void			init_alloc(void)
{
	if (gl_init())
		return ;
	ft_printf("init_alloc() spawned new thread to run main()\n");
	pthread_create(&g_alloc.main_prog, NULL, MAIN_PROGRAM, NULL);
	visualize_th(NULL);
}

PREMAIN_DEF			premain(void)
{
	g_alloc.verbose = ft_strequ(getenv("MALLOC_VERBOSE"), "1");
	init_alloc();
	pthread_join(g_alloc.main_prog, NULL);
	exit(EXIT_SUCCESS);
}
