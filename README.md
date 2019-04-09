# ft_malloc
My own [dynamic memory manager](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation) in C, with OpenGL visualizer. (42 Silicon Valley)

![visualizer](https://github.com/ashih42/ft_malloc/blob/master/Screenshots/visualizer.png)

These functions are implemented:
* malloc
* calloc
* realloc
* free

These functions can be used to inspect blocks of memory:
* show_alloc_mem
* show_alloc_mem_ex

## Prerequisites

You are on macOS with `gcc`, `make`, and `brew` installed.

## Compiling

Build without visualizer

```
./setup.sh no_vis
```

Build with visualizer

```
./setup.sh vis
```

## Linking

Link dynamic library `libft_malloc.so` with `gcc`
```
gcc *.c -L. -lft_malloc
```

## Options

Export environment variables:
* `MALLOC_VISUAL=1` Display the visualizer.
* `MALLOC_VERBOSE=1` Print log of calls to malloc, realloc, calloc, free.

