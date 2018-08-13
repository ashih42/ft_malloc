#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

# define SWAP(a, b, T)		{T temp = a; a = b; b = temp;}

void	show_alloc_mem(void);
void	show_alloc_mem_ex(void);
int		ft_printf(const char *format, ...);

# define ARR_SIZE 10

int			main(void)
{
	srand(time(NULL));
	
	char *array_tiny[ARR_SIZE];
	char *array_small[ARR_SIZE];

	for (int i = 0; i < ARR_SIZE; i++)
	{
		ft_printf("%d\n", i);
		array_tiny[i] = malloc(sizeof(char) * 128);
		array_small[i] = malloc(sizeof(char) * 1024);
	}

	show_alloc_mem();
//	show_alloc_mem_ex();

	sleep(2);

	for (int i = 0; i < ARR_SIZE; i++)
	{
		int j = rand() % ARR_SIZE;
		SWAP(array_tiny[i], array_tiny[j], char *);
		j = rand() % ARR_SIZE;
		SWAP(array_small[i], array_small[j], char *);
	}

	for (int i = 0; i < ARR_SIZE; i++)
	{
		ft_printf("%d\n", i);
		free(array_tiny[i]);
		free(array_small[i]);
	}

	return (0);
}

