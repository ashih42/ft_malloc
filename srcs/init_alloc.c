/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:19:41 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 08:20:04 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc				g_alloc =
{
	{0, 0, 0}, PTHREAD_MUTEX_INITIALIZER, NULL,
	NULL, 0, 0, 0, 0, 0, NULL, 0, 0
};

static void			init_alloc(void)
{
	if (g_alloc.visual)
		g_alloc.visual = !gl_init();
	pthread_create(&g_alloc.main_prog, NULL, MAIN_PROGRAM, NULL);
	if (g_alloc.visual)
		visualize_loop();
	free_visualizer();
}

PREMAIN_DEF			premain(void)
{
	g_alloc.verbose = ft_strequ(getenv("MALLOC_VERBOSE"), "1");
	g_alloc.visual = ft_strequ(getenv("MALLOC_VISUAL"), "1");
	init_alloc();
	pthread_join(g_alloc.main_prog, NULL);
	exit(EXIT_SUCCESS);
}
