/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_init_shader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 00:59:51 by ashih             #+#    #+#             */
/*   Updated: 2018/08/08 19:41:08 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int			compile_shader(unsigned int *id, GLenum type, char *shader)
{
	int				success;
	char			info_log[512];

	*id = glCreateShader(type);
	glShaderSource(*id, 1, (const char *const *)&shader, NULL);
	glCompileShader(*id);
	glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*id, 512, NULL, info_log);
		return (ft_puterror(ERROR_SHADER, info_log, 1));
	}
	return (0);
}

static int			link_shader(unsigned int vs, unsigned int fs)
{
	int				success;
	char			info_log[512];

	g_alloc.shader_prog = glCreateProgram();
	glAttachShader(g_alloc.shader_prog, vs);
	glAttachShader(g_alloc.shader_prog, fs);
	glLinkProgram(g_alloc.shader_prog);
	glGetProgramiv(g_alloc.shader_prog, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(g_alloc.shader_prog, 512, NULL, info_log);
		return (ft_puterror(ERROR_SHADER, info_log, 1));
	}
	glUseProgram(g_alloc.shader_prog);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return (0);
}

int					gl_init_shader(void)
{
	unsigned int	vs;
	unsigned int	fs;

	return (compile_shader(&vs, GL_VERTEX_SHADER, g_alloc.vertex_shader) ||
		compile_shader(&fs, GL_FRAGMENT_SHADER, g_alloc.fragment_shader) ||
		link_shader(vs, fs));
}
