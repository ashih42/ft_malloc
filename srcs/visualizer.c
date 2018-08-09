/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 08:19:24 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 22:05:10 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	free_visualizer(int silent)
{
	if (!silent)
		ft_printf("{bold}{red}Freeing malloc visualizer...{reset}\n");
	g_alloc.main = 0;
	ft_memdel((void **)&g_alloc.frame);
	if (g_alloc.window)
		glfwDestroyWindow(g_alloc.window);
	if (g_alloc.vao)
		glDeleteVertexArrays(1, &g_alloc.vao);
	if (g_alloc.vbo)
		glDeleteBuffers(1, &g_alloc.vbo);
	if (g_alloc.ebo)
		glDeleteBuffers(1, &g_alloc.ebo);
	glfwTerminate();
}

void	visualize_loop(void)
{
	while (!glfwWindowShouldClose(g_alloc.window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, g_alloc.frame_tex);
		pthread_mutex_lock(&g_alloc.mutex);
		render();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIN_WIDTH, WIN_HEIGHT, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, g_alloc.frame);
		pthread_mutex_unlock(&g_alloc.mutex);
		glBindVertexArray(g_alloc.vao);
		glUniform1i(glGetUniformLocation(g_alloc.shader_prog, "frameTex"), 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(g_alloc.window);
		glfwPollEvents();
	}
}
