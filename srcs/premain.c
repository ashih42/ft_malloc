/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   premain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 08:20:04 by ashih             #+#    #+#             */
/*   Updated: 2018/08/11 22:11:51 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

MAIN_DEF			main(void)
{
	(void)0;
}

PREMAIN_DEF			premain(void)
{
	g_alloc.verbose = ft_strequ(getenv("MALLOC_VERBOSE"), "1");
	g_alloc.visual = ft_strequ(getenv("MALLOC_VISUAL"), "1");
	if (g_alloc.visual)
	{
		ft_printf("{bold}{red}Initializing malloc visualizer...{reset}\n");
		g_alloc.visual = !gl_init();
	}
	if (g_alloc.visual)
	{
		ft_printf("{bold}{red}Now executing main()...{reset}\n");
		g_alloc.main = 1;
		pthread_create(&g_alloc.main_prog, NULL, MAIN_PROGRAM, NULL);
		visualize_loop();
		free_visualizer(0);
		pthread_join(g_alloc.main_prog, NULL);
		exit(EXIT_SUCCESS);
	}
	else
		free_visualizer(1);
}
