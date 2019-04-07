# ft_malloc
My own [dynamic memory manager](https://en.wikipedia.org/wiki/C_dynamic_memory_allocation) in C, with OpenGL visualizer. (42 silicon valley)

![visualizer](https://github.com/ashih42/ft_malloc/blob/master/Screenshots/visualizer.png)

These functions are implemented:
* malloc
* realloc
* calloc
* free

## Prerequisites

You are on macOS with `gcc`, `make`, and `brew` installed.

## Compiling the Shared Library

Build without visualizer
```
make all
```

Build with visualizer
```
make vis
```

## Linking the Shared Library

```
gcc *.c -L. -lft_malloc
```

## Options

Export environment variables:
* `MALLOC_VISUAL=1` Display the visualizer.
* `MALLOC_VERBOSE=1` Print log of calls to malloc, realloc, calloc, free.

