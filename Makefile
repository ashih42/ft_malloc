# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ashih <ashih@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/14 05:57:17 by ashih             #+#    #+#              #
#    Updated: 2018/08/16 21:53:29 by ashih            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

GLEW_LOC := $(shell brew --prefix glew)
GLEW_INC := $(GLEW_LOC)/include/
GLEW_LINK := -L $(GLEW_LOC)/lib/ -lGLEW

LIBFT := libft/
LIBFT_INC := $(LIBFT)includes/
LIBFT_LIB := $(LIBFT)libft.a

HEADERS := -I $(INCLUDES) -I $(LIBFT_INC) -I $(GLFW_INC) -I $(GLEW_INC)

CFLAGS := -Wall -Werror -Wextra -fPIC
DLFLAGS := -shared -fPIC

LINK_TARGET := libft_malloc.so

SRCS := alloc.c \
debug.c \
find_block.c \
ft_free.c \
ft_malloc.c \
ft_realloc.c \
hexdump.c \
show_alloc_mem.c \
zone.c \

SRCS_VIS := $(SRCS) \
premain.c \
gl_callback.c \
gl_init.c \
gl_init_shader.c \
draw.c \
render.c \
visualizer.c

SRCDIR := srcs/
OBJDIR := objs/
OBJS := $(addprefix $(OBJDIR), $(SRCS:.c=.o))
OBJS_VIS := $(addprefix $(OBJDIR), $(SRCS_VIS:.c=.o))

no_vis: $(LIBFT_LIB) $(TARGET)
	@echo "Build complete (no visualizer)"

vis: $(LIBFT_LIB) $(TARGET_VIS)
	@echo "Build complete (with visualizer)"

$(LIBFT_LIB):
	@echo "\x1b[1mBuilding $(LIBFT) library...\x1b[0m"
	@make -C $(LIBFT)
	@echo

$(OBJDIR)%.o: $(SRCDIR)%.c
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $(HEADERS) $< -o $@

$(TARGET): $(OBJS)
	@echo "\x1b[1mBuilding $(TARGET)...\x1b[0m"
	$(CC) -o $(TARGET) $(OBJS) $(DLFLAGS) -L$(LIBFT) -lft -lpthread
	/bin/rm -f $(LINK_TARGET)
	@ln -s $(TARGET) $(LINK_TARGET)
	@echo $(LINK_TARGET) is linked to $(TARGET)

$(TARGET_VIS): $(OBJS_VIS)
	@echo "\x1b[1mBuilding $(TARGET_VIS)...\x1b[0m"
	$(CC) -o $(TARGET_VIS) $(OBJS_VIS) $(DLFLAGS) -L$(LIBFT) -lft -lpthread \
		$(GLFW_LINK) $(GLEW_LINK) -framework OpenGL
	/bin/rm -f $(LINK_TARGET)
	@ln -s $(TARGET_VIS) $(LINK_TARGET)
	@echo $(LINK_TARGET) is linked to $(TARGET_VIS)

clean:
	@echo "\x1b[1mCleaning...\x1b[0m"
	make -C $(LIBFT) clean
	/bin/rm -rf $(OBJDIR)
	@echo

fclean: clean
	@echo "\x1b[1mFcleaning...\x1b[0m"
	/bin/rm -f $(LIBFT_LIB)
	/bin/rm -f $(TARGET) $(TARGET_VIS) $(LINK_TARGET)
	@echo

re: fclean no_vis

.PHONY: no_vis vis clean fclean re
