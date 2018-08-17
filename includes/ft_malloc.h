/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashih <ashih@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 07:38:59 by ashih             #+#    #+#             */
/*   Updated: 2018/08/16 21:18:05 by ashih            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <pthread.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

# define FRAME_WIDTH		1000
# define FRAME_HEIGHT		10
# define FRAME_MARGIN		10

# define BLOCKS_DISPLAYED	5

# define WIN_WIDTH		(FRAME_WIDTH + FRAME_MARGIN * 2)
# define WIN_HEIGHT		(FRAME_MARGIN + WIN_HEIGHT_2)
# define WIN_HEIGHT_2	((FRAME_HEIGHT + FRAME_MARGIN) * BLOCKS_DISPLAYED * 2)

# define WIN_NAME			"FT_MALLOC VISUALIZER"
# define ERROR_MEMORY		"Out of memory"
# define ERROR_OPEN_FILE	"Cannot open file"
# define ERROR_GL			"Some kind of OpenGL error"
# define ERROR_SHADER		"Shader error"

# define CHARS_PER_ROW		16

/*
** 16 + (128 + 32) * 100 < 4 * 4096
** 16016 < 16384
*/
# define SMALL_ZONE_SIZE	getpagesize() * 4
# define SMALL_SIZE_CUTOFF	128

/*
** 16 + (1024 + 32) * 100 < 26 * 4096
** 105616 < 106496
*/
# define LARGE_ZONE_SIZE	getpagesize() * 26
# define LARGE_SIZE_CUTOFF	1024

# define MAIN_PROGRAM		((void *(*)(void *))main)

# define SWAP(a, b, T)		{T temp = a; a = b; b = temp;}
# define MAX(a, b)			((a) > (b) ? (a) : (b))
# define MIN(a, b)			((a) < (b) ? (a) : (b))

/*
** Transform x in [min, max] to some new value in [a, b]
*/
# define CHANGE(x, min, max, a, b) (((b)-(a))*((x)-(min))/((max)-(min)))+(a)

# define VERBOSE_PRINT(...)	if (g_alloc.verbose) ft_printf(__VA_ARGS__)

# define KEY_CALLBACK_ARGS int key, int scancode, int action, int mods

# define PREMAIN_DEF void __attribute__ ((constructor))

# define MAIN_DEF int __attribute__ ((weak))

# define VIS_DELAY if (g_alloc.visual && g_alloc.main) usleep(100000)

typedef struct		s_vect2i
{
	int				x;
	int				y;
}					t_vect2i;

/*
** sizeof(t_zone) = 16
*/
typedef struct		s_zone
{
	struct s_zone	*next;
	void			*end;
}					t_zone;

/*
** sizeof(t_block) = 32
*/
typedef struct		s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;
	size_t			checksum;
}					t_block;

enum				e_zone
{
	TINY = 0,
	SMALL,
	LARGE
};

typedef struct		s_alloc
{
	t_zone			*zone[3];

	pthread_mutex_t	mutex;
	pthread_t		main_prog;

	GLFWwindow		*window;
	unsigned int	shader_prog;
	unsigned int	vao;
	unsigned int	vbo;
	unsigned int	ebo;
	unsigned int	frame_tex;
	int				*frame;

	int				verbose;
	int				visual;
	int				main;

	char			*vertex_shader;
	char			*fragment_shader;

}					t_alloc;

extern t_alloc		g_alloc;

/*
** alloc.c
*/
void				*malloc(size_t size);
void				free(void *ptr);
void				*calloc(size_t count, size_t size);
void				*realloc(void *ptr, size_t size);

/*
** debug.c
*/
void				check_checksum(t_block *block);
void				debug_block(t_block *block, t_zone *zone);
void				debug_zone(t_zone *zone);
void				debug_zone_list(t_zone *zone);
void				debug_all_zones(void);

/*
** draw.c
*/
void				draw_line_vert(t_vect2i pos, int len, int color);
void				draw_box(t_vect2i upper_left, t_vect2i dimen, int color);
void				draw_sq(t_vect2i pos, t_vect2i dimen, int color);

/*
** find_block.c
*/
int					find_block_zone(void *ptr, t_block **b, t_zone **z);

/*
** ft_free.c
*/
int					ft_free(void *ptr, size_t *size);

/*
** ft_malloc.c
*/
void				init_next_block(t_zone *zone, t_block *block);
void				*ft_malloc(size_t size);

/*
** ft_realloc.c
*/
void				*ft_realloc(void *ptr, size_t size);

/*
** gl_init.c
*/
int					gl_init(void);

/*
** gl_init_shader.c
*/
int					gl_init_shader(void);

/*
** gl_callback.c
*/
void				key_callback(GLFWwindow *window,
	int key, int scancode, int action, int mods);
void				window_resize_callback(GLFWwindow *window,
	int width, int height);
void				error_callback(int error, const char *description);

/*
** hexdump.c
*/
void				hexdump(t_block *block);

/*
** premain.c
*/

/*
** render.c
*/
void				render(void);

/*
** show_alloc_mem.c
*/
void				show_alloc_mem(void);
void				show_alloc_mem_ex(void);

/*
** visualizer.c
*/
void				free_visualizer(int silent);
void				visualize_loop(void);

/*
** zone.c
*/
void				*new_zone(size_t size);
void				*add_zone(t_zone **zone, t_zone *new);

#endif
