CC := gcc

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

TARGET = libft_malloc_$(HOSTTYPE).so
TARGET_VIS = libft_malloc_vis$(HOSTTYPE).so

INCLUDES := includes/

GLFW_LOC := $(shell brew --prefix glfw)
GLFW_INC := $(GLFW_LOC)/include/
GLFW_LINK := -L $(GLFW_LOC)/lib/ -lglfw
#GLFW_LINK := -L $(GLFW_LOC)/lib/ -Wl -Bstatic -lglfw
#GLFW_LINK := -L $(GLFW_LOC)/lib/ -l:glfw

LIBFT := libft/
LIBFT_INC := $(LIBFT)includes/
LIBFT_LIB := $(LIBFT)libft.a

GLAD_OBJ := objs/glad.o
GLAD_INC := glad/include/


HEADERS := -I $(INCLUDES) -I $(LIBFT_INC) -I $(GLFW_INC) -I $(GLAD_INC)

CFLAGS := -Wall -Werror -Wextra -fPIC #-g -fsanitize=address 
DLFLAGS := -shared 

LINK_TARGET := libft_malloc.so

SRCS := alloc.c \
debug.c \
ft_find_size.c \
ft_free.c \
ft_malloc.c \
hexdump.c \
zone.c \

SRCS_VIS := alloc.c \
debug.c \
ft_find_size.c \
ft_free.c \
ft_malloc.c \
hexdump.c \
zone.c \
premain.c \
gl_callback.c \
gl_init.c \
gl_init_shader.c \
draw.c \
render.c \
show_alloc_mem.c \
visualizer.c


SRCDIR := srcs/
OBJDIR := objs/
OBJS := $(addprefix $(OBJDIR), $(SRCS:.c=.o))
OBJS_VIS := $(addprefix $(OBJDIR), $(SRCS_VIS:.c=.o))

all: $(LIBFT_LIB) $(TARGET)

vis: $(LIBFT_LIB) $(GLAD_OBJ) $(TARGET_VIS)

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
	$(CC) -o $(TARGET) $(OBJS) $(DLFLAGS) -L$(LIBFT) -lft -lpthread
	/bin/rm -f $(LINK_TARGET)
	@ln -s $(TARGET) $(LINK_TARGET)
	@echo $(LINK_TARGET) is linked to $(TARGET)

$(TARGET_VIS): $(OBJS_VIS)
	@echo "\x1b[1mBuilding $(NAME)...\x1b[0m"
	$(CC) -o $(TARGET_VIS) $(OBJS_VIS) $(GLAD_OBJ) $(DLFLAGS) -L$(LIBFT) -lft -lpthread $(GLFW_LINK)
	/bin/rm -f $(LINK_TARGET)
	@ln -s $(TARGET_VIS) $(LINK_TARGET)
	@echo $(LINK_TARGET) is linked to $(TARGET_VIS)

clean:
	@echo "\x1b[1mCleaning...\x1b[0m"
	#make -C $(LIBFT) clean
	/bin/rm -rf $(OBJDIR)
	@echo

fclean: clean
	@echo "\x1b[1mFcleaning...\x1b[0m"
	#/bin/rm -f $(LIBFT_LIB)
	/bin/rm -f $(TARGET) $(TARGET_VIS) $(LINK_TARGET)
	@echo

re: fclean all

.PHONY: all clean fclean re vis
