#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "libft.h"
# include <sys/mman.h>
# include <pthread.h>
# include <mach/thread_act.h>
# include <glad/glad.h>
# include <GLFW/glfw3.h>

#include <stdio.h> // REMOVE

# define SLEEP_TIME					100000

# define FRAME_WIDTH				1000
# define FRAME_HEIGHT				10
# define FRAME_MARGIN				10

# define WIN_WIDTH				(FRAME_WIDTH + FRAME_MARGIN * 2)
# define WIN_HEIGHT				(FRAME_HEIGHT * 3 + FRAME_MARGIN * 4)

# define WIN_NAME				"FT_MALLOC VISUALIZER"
# define ERROR_MEMORY			"Out of memory"
# define ERROR_OPEN_FILE		"Cannot open file"
# define ERROR_GL				"Some kind of OpenGL error"
# define ERROR_SHADER			"Shader error"

# define SMALL_ZONE_SIZE	getpagesize() * 4
# define SMALL_SIZE_CUTOFF	128
/*
** 16 + (128 + 24) * 100 < 4 * 4096
** 15216 < 16384
*/

# define LARGE_ZONE_SIZE	getpagesize() * 26
# define LARGE_SIZE_CUTOFF	1024
/*
** 16 + (1024 + 24) * 100 < 26 * 4096
** 104816 < 106496
*/

# define ENV_MALLOC			"MALLOC_DEBUG"
# define ENV_BLOCKS			"BLOCKS_DEBUG"

# define MAIN_PROGRAM		((void *(*)(void *))main)

# define SWAP(a, b, T)		{T temp = a; a = b; b = temp;}
# define MAX(a, b)			((a) > (b) ? (a) : (b))
# define MIN(a, b)			((a) < (b) ? (a) : (b))

/*
** Transform x in [min, max] to some new value in [a, b]
*/
# define CHANGE(x, min, max, a, b) (((b)-(a))*((x)-(min))/((max)-(min)))+(a)


typedef struct		s_vect2i
{
	int				x;
	int				y;
}					t_vect2i;

/*
** sizeof(t_block) = 16
*/
typedef struct		s_zone
{
	struct s_zone	*next;
	void			*end;
}					t_zone;

/*
** sizeof(t_block) = 24
*/
typedef struct		s_block
{
	size_t			size;
	int				free;
	struct s_block	*next;
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

}					t_alloc;

extern t_alloc		g_alloc;


int					main();




/*
** REQUIRED FUNCTIONS
*/
void			show_alloc_mem(void);
void			show_alloc_mem_ex(void);



/*
** debug.c
*/
void			print_alloc(void);


/*
** draw.c
*/
void			draw_line_vert(t_vect2i pos, int len, int color);
void			draw_box(t_vect2i upper_left, t_vect2i dimen, int color);
void			draw_sq(t_vect2i pos, t_vect2i dimen, int color);


/*
** ft_calloc.c
*/
void			*ft_calloc(size_t count, size_t size);

/*
** ft_free.c
*/
void			ft_free(void *ptr);

/*
** ft_malloc.c
*/
void			*ft_malloc(size_t size);

/*
** ft_realloc.c
*/
void			*ft_realloc(void *ptr, size_t size);


/*
** gl_init.c
*/
int				gl_init(void);

/*
** gl_init_shader.c
*/
int				gl_init_shader(void);

/*
** gl_callback.c
*/
void			key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void			window_resize_callback(GLFWwindow* window, int width, int height);
void			error_callback(int error, const char *description);

/*
** init_alloc.c
*/
void			init_alloc(void);

/*
** render.c
*/
void			render(void);

/*
** visualize_th.c
*/
void			*visualize_th(void *arg);



/*
** zone.c
*/
void			*new_zone(size_t size);
void			*add_zone(t_zone **zone, t_zone *new);










#endif
