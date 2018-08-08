/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_callback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 23:24:47 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 07:33:40 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	key_callback(GLFWwindow *window, KEY_CALLBACK_ARGS)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	(void)scancode;
	(void)mods;
}

void	window_resize_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void	error_callback(int error, const char *description)
{
	ft_printf("error_callback(): Error %d: %s\n", error, description);
}
