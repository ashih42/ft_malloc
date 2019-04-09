#!/bin/sh

echo 'Installing dependencies...'
HOMEBREW_NO_AUTO_UPDATE=1 brew install -v glfw glew

echo 'Building libft_malloc.so...'
make fclean
make $@
