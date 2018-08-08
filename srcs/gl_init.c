/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 23:27:25 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 07:16:14 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int		gl_init_objs(void)
{
	const float			vertices[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f };
	const unsigned int	indices[] = {
		0, 1, 3,
		1, 2, 3 };

	glGenVertexArrays(1, &g_alloc.vao);
	glBindVertexArray(g_alloc.vao);
	glGenBuffers(1, &g_alloc.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, g_alloc.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glGenBuffers(1, &g_alloc.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_alloc.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
		(void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	return (0);
}

static int		init_texture(void)
{
	glGenTextures(1, &g_alloc.frame_tex);
	glBindTexture(GL_TEXTURE_2D, g_alloc.frame_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (!(g_alloc.frame = malloc(sizeof(int) * (WIN_WIDTH) * (WIN_HEIGHT))))
		return (ft_puterror(ERROR_MEMORY, 0, 1));
	return (0);
}

static int		gl_kickstart(void)
{
	glfwSetErrorCallback(error_callback);
	if (glfwInit() == GLFW_FALSE)
		return (ft_puterror(ERROR_GL, 0, 1));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	g_alloc.window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, 0, 0);
	if (!g_alloc.window)
		return (ft_puterror(ERROR_GL, 0, 1));
	glfwMakeContextCurrent(g_alloc.window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return (ft_puterror(ERROR_GL, 0, 1));
	return (0);
}

int				gl_init(void)
{
	int			width;
	int			height;

	if (gl_kickstart() || gl_init_objs() || gl_init_shader() ||
		init_texture())
		return (1);
	glfwGetFramebufferSize(g_alloc.window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetWindowAspectRatio(g_alloc.window, width, height);
	glfwSetFramebufferSizeCallback(g_alloc.window, window_resize_callback);
	glfwSetKeyCallback(g_alloc.window, key_callback);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	return (0);
}
