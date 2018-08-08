/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_init_shader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 00:59:51 by ashih             #+#    #+#             */
/*   Updated: 2018/08/07 03:40:04 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static int			join_lines(int fd, char **str)
{
	char			*line;
	char			*temp;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		temp = *str;
		*str = ft_strjoin(temp, line);
		ft_strdel(&temp);
		if (!*str)
			return (1);
		temp = *str;
		*str = ft_strjoin(temp, "\n");
		ft_strdel(&temp);
		if (!*str)
			return (1);
	}
	return (0);
}

static char			*load_shader(char *filename)
{
	int				error;
	int				fd;
	char			*str;

	error = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		ft_puterror(ERROR_OPEN_FILE, filename, 0);
		return (NULL);
	}
	if (!(str = ft_strnew(0)))
	{
		ft_puterror(ERROR_MEMORY, filename, 0);
		return (NULL);
	}
	join_lines(fd, &str);
	close(fd);
	return (str);
}

static int			compile_shader(unsigned int *id, GLenum type, char *file)
{
	char			*shader_str;
	int				success;
	char			info_log[512];

	*id = glCreateShader(type);
	if (!(shader_str = load_shader(file)))
		return (1);
	glShaderSource(*id, 1, (const char *const *)&shader_str, NULL);
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

	return (compile_shader(&vs, GL_VERTEX_SHADER, "shaders/vertex_shader.vs") ||
		compile_shader(&fs, GL_FRAGMENT_SHADER, "shaders/fragment_shader.fs") ||
		link_shader(vs, fs));
}
