CC := gcc

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

TARGET := asdf_$(HOSTTYPE)
#TARGET = libft_malloc_$(HOSTTYPE).so

INCLUDES := includes/

GLFW_LOC := $(shell brew --prefix glfw)
GLFW_INC := $(GLFW_LOC)/include/
GLFW_LINK := -L $(GLFW_LOC)/lib/ -lglfw

LIBFT := libft/
LIBFT_INC := $(LIBFT)includes/
LIBFT_LIB := $(LIBFT)libft.a

GLAD_OBJ := objs/glad.o
GLAD_INC := glad/include/

CFLAGS := -Wall -Werror -Wextra -g -fsanitize=address 
HEADERS := -I $(INCLUDES) -I $(LIBFT_INC) -I $(GLFW_INC) -I $(GLAD_INC)

CFLAGS := -Wall -Werror -Wextra -g -fsanitize=address 
DLFLAGS := -shared -fPIC

LINK_TARGET := libft_malloc.so

SRCS := main.c \
debug.c \
draw.c \
ft_free.c \
ft_calloc.c \
ft_malloc.c \
ft_realloc.c \
gl_callback.c \
gl_init.c \
gl_init_shader.c \
init_alloc.c \
render.c \
show_alloc_mem.c \
visualize_th.c \
zone.c

SRCDIR := srcs/
OBJDIR := objs/
OBJS := $(addprefix $(OBJDIR), $(SRCS:.c=.o))

FRAMEWORKS := -framework OpenGl

all: glfw $(LIBFT_LIB) $(GLAD_OBJ) $(TARGET)

glfw:
	@echo "\x1b[1mInstalling glfw...\x1b[0m"
	@HOMEBREW_NO_AUTO_UPDATE=1 brew install glfw
	@echo

$(LIBFT_LIB):
	@echo "\x1b[1mBuilding $(LIBFT) library...\x1b[0m"
	@make -C $(LIBFT)
	@echo

$(GLAD_OBJ):
	@echo "\x1b[1mBuilding glad.o...\x1b[0m"
	@gcc glad/src/glad.c -c -I $(GLAD_INC)
	@mkdir -p $(OBJDIR)
	@mv glad.o $(OBJDIR)
	@echo

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(HEADERS) $< -o $@

$(TARGET): $(OBJS)
	@echo "\x1b[1mBuilding $(NAME)...\x1b[0m"
	$(CC) -o $(TARGET) $(OBJS) $(GLAD_OBJ) -L$(LIBFT) -lft -lpthread $(GLFW_LINK) $(FRAMEWORKS) -fsanitize=address
	#$(CC) -o $(TARGET) $(OBJS) $(DLFLAGS) -L$(LIBFT) -lft -lpthread -fsanitize=address
	#/bin/rm -f $(LINK_TARGET)
	#@ln -s $(TARGET) $(LINK_TARGET)
	#@echo $(LINK_TARGET) is linked to $(TARGET)

clean:
	@echo "\x1b[1mCleaning...\x1b[0m"
	#make -C $(LIBFT) clean
	#make -C $(MINILIBX) clean
	/bin/rm -rf $(OBJDIR)
	@echo

fclean: clean
	@echo "\x1b[1mFcleaning...\x1b[0m"
	#/bin/rm -f $(LIBFT_LIB)
	#/bin/rm -f $(MLX_LIB)
	/bin/rm -f $(TARGET)
	/bin/rm -f $(LINK_TARGET)
	@echo

re: fclean all

.PHONY: all clean fclean re
