/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   premain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 08:20:04 by ashih             #+#    #+#             */
/*   Updated: 2018/08/09 21:34:33 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_alloc				g_alloc =
{
	{0, 0, 0}, PTHREAD_MUTEX_INITIALIZER, NULL,
	NULL, 0, 0, 0, 0, 0, NULL, 0, 0, 0,
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

MAIN_DEF			main() {}

PREMAIN_DEF			premain(void)
{
	g_alloc.verbose = ft_strequ(getenv("MALLOC_VERBOSE"), "1");
	g_alloc.visual = ft_strequ(getenv("MALLOC_VISUAL"), "1");
	
	//ft_printf("premain()\n");

	
	if (g_alloc.visual)
	{
		ft_printf("{bold}{red}Initializing malloc visualizer...{reset}\n");
		g_alloc.visual = !gl_init();
	}
	if (g_alloc.visual)
	{
		ft_printf("{bold}{red}Now executing main()...{reset}\n");
		g_alloc.main = 1;

		//ft_printf("spawning thread for main\n");
		pthread_create(&g_alloc.main_prog, NULL, MAIN_PROGRAM, NULL);
		visualize_loop();
		free_visualizer(0);
		pthread_join(g_alloc.main_prog, NULL);
		exit(EXIT_SUCCESS);
	}
	else
		free_visualizer(1);
		
}
